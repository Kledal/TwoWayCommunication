using System;
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

                if (slave.Alarm)
                {
                    item.SubItems.Add("ALARM!");
                }
                else
                {
                    item.SubItems.Add(slave.State);
                }

                item.UseItemStyleForSubItems = false;

                if (slave.State == "Ikke tilgængelig")
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
                        Program.WriteLog("Got status: " + args[1]);
                        int pos = Array.IndexOf(Program._commands, args[1]);
                        Slave s = Program.GetSlaveByAddr(_lastSlave.Address);
                        s.SetState(Program._humancmds[pos]);
                        s.RequestedNewState = false;
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
                        Program.WriteLog("Didnt recognize data: " + data);
                        break;
                }
            }
            catch (Exception e)
            {

            }
        }

        private void logoffBtn_Click(object sender, EventArgs e)
        {
            Program.mode = 0;
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
            Program.GetSerial().SendPublicData(CMD.Open);
            foreach (Slave s in Program.GetSlaves())
            {
                s.RequestedNewState = true;
                s.SetState("Åbner");
            }
            Program.updateSlaves = true;
        }

        private void closeAllBtn_Click(object sender, EventArgs e)
        {
            Program.GetSerial().SendPublicData(CMD.Close);
            foreach (Slave s in Program.GetSlaves())
            {
                s.RequestedNewState = true;
                s.SetState("Lukker");
            }
            Program.updateSlaves = true;
        }

        private string getSelectedAddr()
        {
            string data = "";
            try
            {
                data = unitList.SelectedItems[0].Text;
            }
            catch (Exception e)
            {

            }
            return data;
        }

        private void åbenToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string addr = getSelectedAddr();
            if (addr != "")
            {
                Slave s = Program.GetSlaveByAddr(getSelectedAddr());
                s.RequestedNewState = true;
                s.SetState("Åbner");
                Program.updateSlaves = true;
                Program.WriteLog("Open cmd called on slave: " + s.Address + ".");
                s.SendMessage(CMD.Open);
            }
        }

        private void lukDørToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string addr = getSelectedAddr();
            if (addr != "")
            {
                Slave s = Program.GetSlaveByAddr(getSelectedAddr());
                s.RequestedNewState = true;
                s.SetState("Lukker");
                Program.updateSlaves = true;
                Program.WriteLog("Close cmd called on slave: " + s.Address + ".");
                s.SendMessage(CMD.Close);
            }
        }

        private void opdaterStatusToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string addr = getSelectedAddr();
            if (addr != "")
            {
                Slave s = Program.GetSlaveByAddr(getSelectedAddr());
                Program.WriteLog("Status cmd called on slave: " + s.Address + ".");
                s.SendMessage(CMD.Status);
                _lastSlave = s;
            }
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
            if (Program.mode != 7)
                return;

            //if (!Program.masterReady)
            //    return;

            Slave s = Program.GetSlaves().First();
            if (s.ReadyNextMsg())
            {
                s.SendMessage(CMD.Status);
                _lastSlave = s;
            }
        }

        private void commandQueueTimer_Tick(object sender, EventArgs e)
        {
            if (Program.mode != 7)
                return;

            if (Program.commandqueue.Count == 0)
                return;

            //if (!Program.masterReady)
            //{
            //    Program.WriteLog("Master not ready");
            //    return;
            //}

            //if (Program.GetSlaves().First().ReadyNextMsg())
            Program.GetSerial().SendData( Program.commandqueue.Pop() );
        }
    }
}
