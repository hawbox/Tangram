using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TangramCLR;

namespace MyWpfEclipse
{
    class Program
    {
        // All WPF applications should execute on a single-threaded apartment (STA) thread
        [STAThread]
        public static void Main()
        {
            WpfApplication app = new WpfApplication();
            app.Run();
        }
    }
}
