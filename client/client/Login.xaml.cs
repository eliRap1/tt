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
    /// Interaction logic for Login.xaml
    /// </summary>
    public partial class Login : Page
    {
        public Login()
        {
            InitializeComponent();
        }

        private void btnLogin_Click(object sender, RoutedEventArgs e)
        {
            string username = txtUsername.Text.Trim();
            string password = txtPassword.Password.Trim();

            if (string.IsNullOrEmpty(username) || string.IsNullOrEmpty(password))
            {
                MessageBox.Show("Please enter both username and password.");
                return;
            }

            try
            {

                byte[] request = Serializer.serializeLoginRequest(username, password);
                byte[] response = Communicator.sendAndReceive(request);

                int status = Deserializer.extractStatus(response);

                if (status == 1)
                {
                    this.NavigationService?.Navigate(new Trivia());
                }
                else
                {
                    MessageBox.Show("Login failed. Incorrect credentials.");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error: " + ex.Message);
            }
        }

        private void btnSignUp_Click(object sender, RoutedEventArgs e)
        {
            LogInFrame.Navigate(new SignUp());
        }
    }
}
