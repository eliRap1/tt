using System;
using System.Globalization;
using System.Text.RegularExpressions;
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
    public partial class SignUp : Page
    {
        private User user;
        public SignUp()
        {
            InitializeComponent();
            user = new User();
            this.DataContext = user;
        }

        private void txtPassword_PasswordChanged(object sender, RoutedEventArgs e)
        {
            if (!Regex.IsMatch(txtPassword.Password, @"^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{6,20}$"))
            {
                txtPassword.BorderBrush = Brushes.Red;
                txtPassword.ToolTip = "Password must be 6–20 characters with letters and digits.";
                txtPassword.Tag = "error";
            }
            else
            {
                txtPassword.ToolTip = null;
                txtPassword.Tag = "";
            }
        }

        private void btnSignUp_Click(object sender, RoutedEventArgs e)
        {
            if (Validation.GetHasError(txtEmail) ||
                Validation.GetHasError(txtUsername) ||
                txtPassword.Tag?.ToString() == "error")
            {
                MessageBox.Show("Please correct the highlighted fields.");
                return;
            }

            string username = txtUsername.Text.Trim();
            string password = txtPassword.Password.Trim();
            string email1 = txtEmail.Text.Trim();

            try
            {
                byte[] request = Serializer.serializeSignupRequest(username, password, email1);
                byte[] response = MainWindow.communicator.sendAndReceive(request);
                int status = Deserializer.extractStatus(response);

                if (status == 2)
                {
                    SignuUpFrame.Navigate(new Trivia());
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
            this.DataContext = null;
            SignuUpFrame.Navigate(new Login());
        }
    }
}
