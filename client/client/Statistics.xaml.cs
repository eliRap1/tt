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
        }

        private void HighScores_Click(object sender, RoutedEventArgs e)
        {
            statisticsFrame.Navigate(new recordGrid());
        }

        private void PersonalStats_Click(object sender, RoutedEventArgs e)
        {
            statisticsFrame.Navigate(new personalRecord());
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            statisticsFrame.Navigate(new Trivia());
        }   
    }
}
