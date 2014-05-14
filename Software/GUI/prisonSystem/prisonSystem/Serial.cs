using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO.Ports;

namespace prisonSystem
{
    class Serial
    {
        private SerialPort _port;

        public delegate void dataReceived(object source, string data);
        public event dataReceived DataReceived;

        private StringBuilder _buffer = new StringBuilder();

        public Serial(string comport = "COM5")
        {
            try
            {
                //this setup must be the same on STK500
                // set as 8 bit data, no parity bit and 1 stop bit.
                _port = new SerialPort(comport, 9600, Parity.None, 8, StopBits.One);
                _port.DataReceived += _port_DataReceived;
                _port.Open();
                Program.WriteLog("Connected successful via serial.");
            }
            catch (Exception e)
            {
                Program.WriteLog("Failed to connect via serial connection.");
            }
        }

        public SerialPort Port
        {
            get { return _port; }
        }

        public void SendData(string data)
        {
            if (!_port.IsOpen)
                return;

            byte[] buffer = Encoding.ASCII.GetBytes(data + (char)13);
            _port.Write(buffer, 0, buffer.Length);

            Program.WriteLog("Data transmitted via serial: " + data);
        }

        void _port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            if (DataReceived != null)
            {
                int _char = _port.ReadChar();
                if (_char == 13)
                {
                    DataReceived(this, _buffer.ToString());
                    Program.WriteLog("Data received via serial: " + _buffer.ToString());
                    _buffer = new StringBuilder();
                }
                else
                {
                    _buffer.Append( ((char)_char).ToString());
                }
            }
        }

    }
}
