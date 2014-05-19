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
    public partial class LogForm : Form
    {
        public LogForm()
        {
            InitializeComponent();
        }

        private void LogForm_Load(object sender, EventArgs e)
        {
            InsertLogs();
            logTimer.Start();
        }

        private void InsertLogs()
        {
            logListView.Items.Clear();
            List<string> logs = Program.GetLog();
            foreach (string msg in logs)
            {
                ListViewItem li = new ListViewItem(msg);
                logListView.Items.Add(li);
            }
            logListView.Items[logListView.Items.Count - 1].EnsureVisible();
        }

        private void logTimer_Tick(object sender, EventArgs e)
        {
            if (logListView.Items.Count < Program.GetLog().Count)
            {
                InsertLogs();
            }
        }
    }
}
