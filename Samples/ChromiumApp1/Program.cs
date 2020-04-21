using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using TangramCLR;

namespace ChromiumApp1
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            // Important! Don't move this line.
            if (!Tangram.WebRuntimeInit)
            {
                // We don't need to specify the main window here.
                Application.Run();
            }
        }
    }
}
