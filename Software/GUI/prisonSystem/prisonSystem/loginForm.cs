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
    public partial class loginForm : Form
    {        

        public loginForm()
        {
            InitializeComponent();
        }

        public void changeStatusMessage(string message, Color color)
        {
            statusLbl.Text = message;
            statusLbl.ForeColor = color;
            statusLbl.TextAlign = ContentAlignment.MiddleCenter;
        }

        private void testBtn_Click(object sender, EventArgs e)
        {
            Program.mode = 7;
            openMainWindow();
             
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            updateStatusTxt();
        }

        public void updateStatusTxt()
        {
            switch (Program.mode)
            {
                case 0:
                    changeStatusMessage("Kontroller forbindelse..", Color.Blue);
                    Program.GetSerial().SendData("O");
                    break;
                case 1:
                    changeStatusMessage("Forbundet til STK500..", Color.Green);
                    Program.mode = 3;
                    break;
                case 3:
                    changeStatusMessage("Afventer kodeindtast fra DE2 board..", Color.Blue);
                    Program.GetSerial().SendData("S");
                    break;
                case 5:
                    changeStatusMessage("Koden er blevet godkendt, nulstil alle pins på DE2 boardet..", Color.Green);
                    Program.GetSerial().SendData("S");
                    break;
                case 7:
                    openMainWindow();
                    break;
            }
        }

        private void openMainWindow()
        {
            Form1 form = (Form1)this.Tag;
            form.shouldHide = false;
            form.Show();

            this.Close();
        }

        private void loginForm_Load(object sender, EventArgs e)
        {
            timer1.Interval = 1000;
            timer1.Enabled = true;
            timer1.Start();

            Program.GetSerial().SendData("O");
        }

    }
}
