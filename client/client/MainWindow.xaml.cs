using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public static Communicator communicator;
        public MainWindow()
        {
            InitializeComponent();
            TcpClient client = new TcpClient();
            communicator = new Communicator(client);
            communicator.connect();
            Closing += MainWindow_Closing;
        }

        private void btnLogin_Click(object sender, RoutedEventArgs e)
        {
            MainFrame.Navigate(new Login());
        }

        private void btnSignUp_Click(object sender, RoutedEventArgs e)
        {
            MainFrame.Navigate(new SignUp());
        }
        private async void MainWindow_Closing(object sender, CancelEventArgs e)
        {
            e.Cancel = true;
            communicator.sendAndReceive(Serializer.serializeLogoutRequest(Login.user));
            e.Cancel = false;

        }
    }
}
