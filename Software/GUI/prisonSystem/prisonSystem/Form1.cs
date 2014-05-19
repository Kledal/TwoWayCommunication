﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace prisonSystem
{
    public partial class Form1 : Form
    {
        public bool shouldHide = true;
        private string _port = "COM3";

        private Slave _lastSlave = null;

        public Form1()
        {
            InitializeComponent();
        }

        protected override void OnVisibleChanged(EventArgs e)
        {
            base.OnVisibleChanged(e);
            if (shouldHide)
                this.Visible = false;
        }

        public void Setup()
        {
            Program.SetupSerial(_port);
        }

        void showLoginForm()
        {
            LogForm logf = new LogForm();
            logf.Show();
            loginForm lf = new loginForm();
            lf.Tag = this;
            lf.Show();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Setup();
            Program.GetSerial().DataReceived += Form1_DataReceived;
            RedrawSlaves();

            showLoginForm();
        }

        private void RedrawSlaves()
        {
            unitList.Items.Clear();
            foreach (Slave slave in Program.GetSlaves())
            {
                ListViewItem item = new ListViewItem();
                item.Text = slave.Address;

                item.SubItems.Add(slave.Name);
                item.SubItems.Add(slave.State);

                item.UseItemStyleForSubItems = false;
                item.SubItems[2].ForeColor = Color.Red;

                unitList.Items.Add(item);
            }
        }

        void Form1_DataReceived(object source, string data)
        {
            try
            {
                string header = data.Substring(0, 1);
                string[] args = data.Split(':');
                switch (header)
                {
                    case "O":
                        Program.mode = 1;
                        Program.WriteLog("Got online status from STK500.");
                        break;
                    case "S":
                        int pos = Array.IndexOf(Program._commands, args[1]);
                        Program.GetSlaveByAddr(_lastSlave.Address).SetState(Program._humancmds[pos]);
                        Program.updateSlaves = true;
                        break;
                    case "K":
                        Program.mode = 5;
                        break;
                    case "L":
                        if (Program.mode == 5)
                            Program.mode = 7;
                        break;
                    case "R": // Master is ready again.
                        Program.WriteLog("Master is ready again.");
                        Program.masterReady = true;
                        break;
                    default:
                        //Program.WriteLog("Didnt recognize data: " + data);
                        break;
                }
            }
            catch (Exception e)
            {

            }
        }

        private void logoffBtn_Click(object sender, EventArgs e)
        {
            this.shouldHide = false;
            this.Hide();
            showLoginForm();
        }

        private void openLogBtn_Click(object sender, EventArgs e)
        {
            LogForm lg = new LogForm();
            lg.Show();
        }

        private void openAllBtn_Click(object sender, EventArgs e)
        {
            Program.GetSerial().SendData(Program._commands[(int)CMD.StartBit] + Program.publicAddress + Program._commands[(int)CMD.Open]);
        }

        private void closeAllBtn_Click(object sender, EventArgs e)
        {
            Program.GetSerial().SendData(Program._commands[(int)CMD.StartBit] + Program.publicAddress + Program._commands[(int)CMD.Close]);
        }

        private string getSelectedAddr()
        {
            return unitList.SelectedItems[0].Text;
        }

        private void åbenToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Slave s = Program.GetSlaveByAddr(getSelectedAddr());
            s.SetState("Åbner");
            Program.WriteLog("Open cmd called on slave: " + s.Address + ".");
            s.SendMessage(CMD.Open);
        }

        private void lukDørToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Slave s = Program.GetSlaveByAddr(getSelectedAddr());
            s.SetState("Lukker");
            Program.WriteLog("Close cmd called on slave: " + s.Address + ".");
            s.SendMessage(CMD.Close);
        }

        private void opdaterStatusToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Slave s = Program.GetSlaveByAddr(getSelectedAddr());
            Program.WriteLog("Status cmd called on slave: " + s.Address + ".");
            s.SendMessage(CMD.Status);
            _lastSlave = s;
        }

        private void slaveUpdateTimer_Tick(object sender, EventArgs e)
        {
            if (Program.updateSlaves)
            {
                RedrawSlaves();
                Program.updateSlaves = false;
            }
        }

        private void slaveStatusTimer_Tick(object sender, EventArgs e)
        {
            if (!Program.masterReady)
                return;

            Slave s = Program.GetSlaves().First();
            s.SendMessage(CMD.Status);
            _lastSlave = s;
        }

        private void commandQueueTimer_Tick(object sender, EventArgs e)
        {
            if (Program.commandqueue.Count == 0)
                return;

            if (!Program.masterReady)
            {
                Program.WriteLog("Master not ready");
                return;
            }

            Program.GetSerial().SendData( Program.commandqueue.Pop() );
        }
    }
}
