using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TangramCLR;

namespace MyWpfBrowser
{
    class Program
    {
        // All WPF applications should execute on a single-threaded apartment (STA) thread
        [STAThread]
        public static void Main()
        {
            WpfApp app = new WpfApp();
            app.UpdateNewTabPageLayout("Default_Wpf.xml");
            app.Run();
        }
    }
}
