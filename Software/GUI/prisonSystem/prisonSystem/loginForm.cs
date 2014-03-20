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
        int mode = 0;

        public loginForm()
        {
            InitializeComponent();
        }

        private void loginForm_Load(object sender, EventArgs e)
        {

        }

        public void changeStatusMessage(string message, Color color)
        {
            statusLbl.Text = message;
            statusLbl.ForeColor = color;
            statusLbl.TextAlign = ContentAlignment.MiddleCenter;
        }

        private void testBtn_Click(object sender, EventArgs e)
        {
            //openMainWindow();
            
            timer1.Interval = 1000;
            timer1.Enabled = true;
            timer1.Start();
             
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            switch (mode)
            {
                case 0:
                    changeStatusMessage("Forbundet til STK500..", Color.Blue);
                    break;
                case 3:
                    changeStatusMessage("Afventer kodeindtast fra DE2 board..", Color.Blue);
                    timer1.Stop();
                    break;
                case 5:
                    changeStatusMessage("Koden er blevet godkendt, nulstil alle pins på DE2 boardet..", Color.Green);
                    break;
                case 7:
                    openMainWindow();

                    break;
            }
            mode++;
        }

        private void openMainWindow()
        {
            Form1 form = (Form1)this.Tag;
            form.shouldHide = false;
            form.Show();

            this.Close();
        }

    }
}
