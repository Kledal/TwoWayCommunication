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

        public Form1()
        {
            InitializeComponent();
        }

        private void loginBtn_Click(object sender, EventArgs e)
        {
            
        }

        protected override void OnVisibleChanged(EventArgs e)
        {
            base.OnVisibleChanged(e);
            if (shouldHide)
                this.Visible = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            loginForm lf = new loginForm();
            lf.Tag = this;
            lf.Show();

            try
            {
                ListViewItem item = new ListViewItem();
                item.Text = "00101010";

                item.SubItems.Add("Hoveddør");
                item.SubItems.Add("Lukket");
                item.SubItems.Add("Button");

                item.UseItemStyleForSubItems = false;
                item.SubItems[2].ForeColor = Color.Red;

                unitList.Items.Add(item);
            }
            catch (Exception ee)
            {
                MessageBox.Show(ee.ToString());
            }
        }
    }
}
