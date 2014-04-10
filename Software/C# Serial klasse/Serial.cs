using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO.Ports;

namespace TestSerial
{
    class Serial
    {
        private SerialPort _port;

        public delegate void dataReceived(object source, string data);
        public event dataReceived DataReceived;

        public Serial(string comport = "COM5")
        {
            //this setup must be the same on STK500
            // set as 8 bit data, no parity bit and 1 stop bit.
            _port = new SerialPort(comport, 9600, Parity.None, 8, StopBits.One);
            _port.DataReceived += _port_DataReceived;
            _port.Open();
        }

        public SerialPort Port
        {
            get { return _port; }
        }

        public void SendData(string data)
        {
            if (!_port.IsOpen)
                return;

            byte[] buffer = Encoding.ASCII.GetBytes(data);
            _port.Write(buffer, 0, buffer.Length);
        }

        void _port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            if (DataReceived != null)
                DataReceived(this, _port.ReadExisting());
        }

    }
}
