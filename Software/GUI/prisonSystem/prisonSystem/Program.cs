using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace prisonSystem
{
    enum CMD : int { Open, Close, Status, StartBit }

    static class Program
    {
        static Serial _serial;
        static List<string> _log;

        static List<Slave> _slaves;

        static public string[] _commands = { "1100", "0011", "1111", "01110" };
        static public string[] _humancmds = { "Åben", "Lukket", "Ikke tilgængelig" };

        static public string publicAddress = "10101010";

        static public int mode = 0;
        static public bool updateSlaves = false;

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            _log = new List<string>();
            _slaves = new List<Slave>();

            _slaves.Add(new Slave("11001100", "Test slave", "Ikke tilgængelig"));

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }

        public static void SetupSerial(string comport)
        {
            _serial = new Serial(comport);
        }
        public static Serial GetSerial()
        {
            return _serial;
        }
        public static List<Slave> GetSlaves()
        {
            return _slaves;
        }
        public static Slave GetSlaveByAddr(string addr)
        {
            return _slaves.Find(o => o.Address == addr);
        }
        public static List<string> GetLog()
        {
            return _log;
        }
        public static void WriteLog(string msg)
        {
            string dato = DateTime.Now.ToString("yyyy-MM-ddTHH:mm:ss").ToString();
            _log.Add(dato + ": " + msg);
        }
    }
}
