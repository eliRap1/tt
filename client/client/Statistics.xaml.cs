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
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class Statistics : Page
    {
        public Statistics()
        {
            InitializeComponent();
            statisticsFrame.NavigationUIVisibility = System.Windows.Navigation.NavigationUIVisibility.Hidden;
            statisticsFrame.Visibility = Visibility.Collapsed;
        }

        private void HighScores_Click(object sender, RoutedEventArgs e)
        {
            menuPanel.Visibility = Visibility.Collapsed;
            statisticsFrame.Visibility = Visibility.Visible;
            statisticsFrame.Navigate(new recordGrid());
        }

        private void PersonalStats_Click(object sender, RoutedEventArgs e)
        {
            menuPanel.Visibility = Visibility.Collapsed;
            statisticsFrame.Visibility = Visibility.Visible;
            statisticsFrame.Navigate(new personalRecord());
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            if (statisticsFrame.CanGoBack)
            {
                statisticsFrame.GoBack();
            }
            else
            {
                menuPanel.Visibility = Visibility.Visible;
                statisticsFrame.Visibility = Visibility.Collapsed;
            }
        }   
    }
}
