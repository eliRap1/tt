using System;
using System.Collections.Generic;
using System.Linq;
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
    /// Interaction logic for Trivia.xaml
    /// </summary>
    public partial class Trivia : Page
    {
        public Trivia()
        {
            InitializeComponent();
        }

        private void CreateRoom_Click(object sender, RoutedEventArgs e)
        {
            MainFrame.Navigate(new CreateRoom());
        }

        private void JoinRoom_Click(object sender, RoutedEventArgs e)
        {
            MainFrame.Navigate(new JoinRoom());
        }

        private void Statistics_Click(object sender, RoutedEventArgs e)
        {
            //TO DO (IDAN)
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            byte[] request = Serializer.serializeLogoutRequest(Login.user);
            byte[] response = MainWindow.communicator.sendAndReceive(request);
            MainWindow.communicator.close();
            System.Windows.Application.Current.Shutdown();// shut down the application
        }

    }
}
