using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace prisonSystem
{
    class Slave
    {
        private string _addr;
        private string _state;
        private string _name;

        public Slave(string addr, string name, string state)
        {
            _addr = addr;
            _name = name;
            _state = state;
        }

        public void SendMessage(CMD message)
        {
            Program.GetSerial().SendData(Program._commands[(int)CMD.StartBit] + _addr + Program._commands[(int)message]);
        }

        public void SetState(string state)
        {
            _state = state;
        }

        public string Address { get { return _addr; } }
        public string State { get { return _state; } }
        public string Name { get { return _name; } }
    }
}
