﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Lego.Ev3.Core;
using Lego.Ev3.Desktop;
using KafkaNet;
using KafkaNet.Model;
using KafkaNet.Protocol;
using System.Threading;

namespace MindStorm
{
    public partial class Form1 : Form
    {
        Brick _brick;
        OutputPort porta = OutputPort.All;
        KafkaOptions options;
        BrokerRouter router;
        KafkaNet.Producer client;
        bool bloquear;
        Consumer consumer;

        public Form1()
        {
            InitializeComponent();
            foreach (var item in SerialPort.GetPortNames())
            {
                comboBox1.Items.Add(item);
            }
            comboBox2.SelectedIndex = 0;

            bloquear = true;
            options = new KafkaOptions(new Uri("http://35.202.217.21:9092"));
            //options = new KafkaOptions(new Uri("http://192.168.1.30:9092"));
            router = new BrokerRouter(options);
            client = new KafkaNet.Producer(router);
            consumer = new Consumer(new ConsumerOptions("Teste", router));
            Thread _lekafka = new Thread(leKafka);
            _lekafka.Start();
        }

        public void leKafka()
        {            
            foreach (var message in consumer.Consume())
            {
                var _offset = consumer.GetOffsetPosition();
                this.Invoke(new MethodInvoker(() =>
                {
                    if (message.Meta.Offset >= (_offset[0].Offset - 1))
                    {
                        if (!bloquear)
                        {
                            textBox4.AppendText(DateTime.Now.ToString("h:mm:ss ") + " RECEBEU: " +
                             System.Text.Encoding.Default.GetString(message.Value) + Environment.NewLine);
                        }
                        else
                        {
                            bloquear = false;
                        }
                    }
                }));
            }
        }

        private void button9_Click(object sender, EventArgs e)
        {
            textBox4.AppendText(DateTime.Now.ToString("h:mm:ss ") + " ENVIANDO TESTE" + Environment.NewLine);
            client.SendMessageAsync("Teste", new[] { new KafkaNet.Protocol.Message("TESTE") });
        }

        public void log(string text)
        {
            textBox3.AppendText(DateTime.Now.ToString("h:mm:ss ") + text + Environment.NewLine);
        }

        public async void button1_Click(object sender, EventArgs e)
        {
            try
            {
                button1.Enabled = false;
                _brick = new Brick(new BluetoothCommunication(comboBox1.SelectedItem.ToString()));
                await _brick.ConnectAsync();
                comboBox1.Enabled = false;
                button3.Enabled = false;
                button2.Enabled = true;
                button4.Enabled = true;
                button5.Enabled = true;
                button6.Enabled = true;
                comboBox2.Enabled = true;
                textBox1.Enabled = true;
                textBox2.Enabled = true;
                textBox5.Enabled = true;
                button7.Enabled = true;
                button8.Enabled = true;
                log("Conectado!");
            }
            catch (Exception Ex)
            {
                button1.Enabled = true;
                MessageBox.Show("Erro ao conectar:" + Ex.Message);
            }
        }

        public async void button2_Click(object sender, EventArgs e)
        {
            log("Beep");
            await _brick.DirectCommand.PlayToneAsync(100, 1000, 300);
        }

        public void button3_Click(object sender, EventArgs e)
        {
            comboBox1.Items.Clear();
            foreach (var item in SerialPort.GetPortNames())
            {
                comboBox1.Items.Add(item);
            }
        }

        public void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (comboBox2.SelectedIndex)
            {
                case 0:
                    porta = OutputPort.All;
                    break;
                case 1:
                    porta = OutputPort.A;
                    break;
                case 2:
                    porta = OutputPort.B;
                    break;
                case 3:
                    porta = OutputPort.C;
                    break;
                case 4:
                    porta = OutputPort.D;
                    break;
            }
        }

        public void button4_Click(object sender, EventArgs e)
        {
            log("Movendo para Cima | Velocidade: " + textBox1.Text + " | Tempo: " + textBox2.Text + " ms");
            _brick.DirectCommand.SetMotorPolarity(porta, Polarity.Forward);
            _brick.DirectCommand.TurnMotorAtSpeedForTimeAsync(porta, Convert.ToInt32(textBox1.Text), Convert.ToUInt32(textBox2.Text), false);
        }

        public void button5_Click(object sender, EventArgs e)
        {
            log("Movendo para Baixo | Velocidade: " + textBox1.Text + " | Tempo: " + textBox2.Text + " ms");
            _brick.DirectCommand.SetMotorPolarity(porta, Polarity.Backward);
            _brick.DirectCommand.TurnMotorAtSpeedForTimeAsync(porta, Convert.ToInt32(textBox1.Text), Convert.ToUInt32(textBox2.Text), false);
        }

        public void button6_Click(object sender, EventArgs e)
        {
            _brick.DirectCommand.StopMotorAsync(OutputPort.All, false);
        }

        public void button7_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < Convert.ToInt32(textBox5.Text); i++)
            {
                log("Andando " + Convert.ToInt32(textBox5.Text) + " passos| Velocidade: " + textBox1.Text + " | Tempo: " + textBox2.Text + " ms");

                _brick.DirectCommand.SetMotorPolarity(OutputPort.A, Polarity.Forward);
                _brick.DirectCommand.TurnMotorAtSpeedForTimeAsync(OutputPort.A, Convert.ToInt32(textBox1.Text), Convert.ToUInt32(textBox2.Text), false);
                _brick.DirectCommand.SetMotorPolarity(OutputPort.B, Polarity.Backward);
                _brick.DirectCommand.TurnMotorAtSpeedForTimeAsync(OutputPort.B, Convert.ToInt32(textBox1.Text), Convert.ToUInt32(textBox2.Text), false);

                Thread.Sleep(1000);

                _brick.DirectCommand.SetMotorPolarity(OutputPort.A, Polarity.Backward);
                _brick.DirectCommand.TurnMotorAtSpeedForTimeAsync(OutputPort.A, Convert.ToInt32(textBox1.Text), Convert.ToUInt32(textBox2.Text), false);
                _brick.DirectCommand.SetMotorPolarity(OutputPort.B, Polarity.Forward);
                _brick.DirectCommand.TurnMotorAtSpeedForTimeAsync(OutputPort.B, Convert.ToInt32(textBox1.Text), Convert.ToUInt32(textBox2.Text), false);

                Thread.Sleep(1000);

            }
        }

        public void button8_Click(object sender, EventArgs e)
        {
            _brick.DirectCommand.SetMotorPolarity(OutputPort.All, Polarity.Backward);
            for (int i = 0; i < 50; i++)
            {
                _brick.DirectCommand.TurnMotorAtSpeedForTimeAsync(OutputPort.All, 70, 90, false);
                Thread.Sleep(100);
            }

        }


    }
}
