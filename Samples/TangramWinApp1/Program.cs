/********************************************************************************
*					Tangram Wizard - version 1.0.0							*
*********************************************************************************
* Copyright (C) 2002-2020 by Tangram Team.   All Rights Reserved.				*
*
* THIS SOURCE FILE IS THE PROPERTY OF TANGRAM TEAM AND IS NOT TO
* BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED
* WRITTEN CONSENT OF TANGRAM TEAM.
*
* THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS
* OUTLINED IN THE GPL LICENSE AGREEMENT.TANGRAM TEAM
* GRANTS TO YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE
* THIS SOFTWARE ON A SINGLE COMPUTER.
*
* CONTACT INFORMATION:
* mailto:tangramteam@outlook.com
* https://www.tangram.dev
*
*
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

using TangramCLR;

namespace TangramWinApp1
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
            if (Tangram.BuiltInBrowserModel == true)
                return;
            string newTabPageLayout = Helper.LoadResourceFile("TangramWinApp1.Default.xml");
            Tangram.UpdateNewTabPageLayout(newTabPageLayout);
            Tangram.WizData = "TangramWinApp1.wizxml";

            //Support Application Type:
            //Application is a Chromium Based WebBrowser
            //Tangram.AppType = TangramAppType.APP_BROWSER;

            //Application is a Chromium Based Desktop Application
            //Tangram.AppType = TangramAppType.APP_BROWSERAPP;

            //Application is a Chromium-Eclipse Based Desktop Application, Need Eclipse Binary Component and 64bit JVM
            //Tangram.AppType = TangramAppType.APP_BROWSER_ECLIPSE; 
            //Application is a Customized Eclipse IDE, Need Eclipse Binary Component and 64bit JVM
            //Tangram.AppType = TangramAppType.APP_ECLIPSE;
            //Application is a Win32 Desktop App
            //Tangram.AppType = TangramAppType.APP_WIN32;

            switch (Tangram.AppType)
            {
                case TangramAppType.APP_BROWSER:
                case TangramAppType.APP_BROWSERAPP:
                    break;
                case TangramAppType.APP_BROWSER_ECLIPSE:
                    {
                        Tangram.MainForm = Tangram.Context.MainForm = new TangramWinApp1MDIForm();

                        Tangram.Context.MainForm.Show();
                    }
                    break;
                case TangramAppType.APP_ECLIPSE:
                    {
                        Tangram.MainForm = Tangram.Context.MainForm = new TangramWinApp1MDIForm();
                        Tangram.Context.MainForm.Show();
                    }
                    break;
                case TangramAppType.APP_WIN32:
                    {
                        Tangram.MainForm = Tangram.Context.MainForm = new TangramWinApp1MDIForm();

                        Tangram.Context.MainForm.Show();
                    }
                    break;
                default:
                    {
                        Tangram.MainForm = Tangram.Context.MainForm = new TangramWinApp1MDIForm();

                        Tangram.Context.MainForm.Show();
                    }
                    break;
            }

            Application.Run(Tangram.Context);
        }
    }
}
