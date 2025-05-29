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
using System.Threading;
using System.Windows.Threading;

namespace client
{
    /// <summary>
    /// Interaction logic for Room.xaml
    /// </summary>
    public partial class Room : Page
    {
        private RoomInfo room1;
        private DispatcherTimer updatePlayersTimer;
        public Room(RoomInfo room, string admin = "")
        {
            InitializeComponent();
            this.room1 = room;
            roomName.Text = room.name;
            roomId.Text = room.id.ToString();
            questionAmount.Text = room.numOfQuestionsInGame.ToString();
            timePerQuestion.Text = $"{room.timePerQuestion} sec";
            CheckPlayers(null, EventArgs.Empty);
            if (admin != "")
            {
                adminName.Text = admin;
                start.Visibility = Visibility.Visible;
            }
                updatePlayersTimer = new DispatcherTimer(); // POOLING THREAD /credit to my mekif z teacher
            updatePlayersTimer.Interval = TimeSpan.FromSeconds(3);
            updatePlayersTimer.Tick += CheckPlayers;
            updatePlayersTimer.Start();

        }
        private void CheckPlayers(object sender, EventArgs e)
        {
            byte[] request = Serializer.SearalizeGetPlayersInRoomRequest(room1.id);
            byte[] response = MainWindow.communicator.sendAndReceive(request);
            List<string> players = Deserializer.DeserializeGetPlayersInRoomResponse(response);
            playersList.ItemsSource = players;
            adminName.Text = players[0];
            if(Login.user == players[0])
            {
                start.Visibility = Visibility.Visible;
            }
        }
        public static int CheckPlayersList(int roomId)
        {
            byte[] request = Serializer.SearalizeGetPlayersInRoomRequest(roomId);
            byte[] response = MainWindow.communicator.sendAndReceive(request);
            List<string> players = Deserializer.DeserializeGetPlayersInRoomResponse(response);
            return players.Count;
        }
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            byte[] request = Serializer.serializeLogoutRequest(Login.user);
            byte[] response = MainWindow.communicator.sendAndReceive(request);
            request = Serializer.serializeLoginRequest(Login.user, Login.pass);
            response = MainWindow.communicator.sendAndReceive(request);
            updatePlayersTimer.Stop();
            triviaF.Navigate(new Trivia());
        }
    }
}
