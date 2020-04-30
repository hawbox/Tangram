using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp4
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
            
			/// Begin Add By TangramTeam
			/// Thank you for using the Web Runtime for Application migration tool;
			/// by using this wizard, first we will replace "Application.Run" with "TangramCLR.Tangram.RunForTest",
			/// so that you can experience the charm of Web Runtime for Application at the first time, 
			/// once you decide to adopt Web Runtime for Application to migrate your application system or develop your new application, 
			/// you need to replace "TangramCLR.Tangram.RunForTest" with "TangramCLR.Tangram.Run", 
			/// so you will officially start your development work.
			/// If you have any specific suggestions, you can directly contact us, thanks.
			/// End Add By TangramTeam
			TangramCLR.Tangram.Run(new MDIParent1());
        }
    }
}
