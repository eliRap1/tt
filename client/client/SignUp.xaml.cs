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
    /// Interaction logic for SignUp.xaml
    /// </summary>
    public partial class SignUp : Page
    {
        public SignUp()
        {
            InitializeComponent();
        }

        private void btnSignUp_Click(object sender, RoutedEventArgs e)
        {
            string username = txtUsername.Text.Trim();
            string password = txtPassword.Password.Trim();
            string email = txtEmail.Text.Trim();

            if (string.IsNullOrEmpty(username) || string.IsNullOrEmpty(password) || string.IsNullOrEmpty(email))
            {
                MessageBox.Show("Please fill in all fields.");
                return;
            }

            try
            {
                byte[] request = Serializer.serializeSignupRequest(username, password, email);
                byte[] response = Communicator.sendAndReceive(request);
                int status = Deserializer.extractStatus(response);

                if (status == 2)
                {
                    this.NavigationService?.Navigate(new Trivia());
                }
                else
                {
                    MessageBox.Show("Signup failed. Please try a different username or check your input.");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error: " + ex.Message);
            }
        }

    private void btnLogin_Click(object sender, RoutedEventArgs e)
        {
            SignuUpFrame.Navigate(new Login());
        }
    }
}
