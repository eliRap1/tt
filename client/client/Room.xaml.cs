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
    /// Interaction logic for Room.xaml
    /// </summary>
    public partial class Room : Page
    {
        public Room(RoomInfo room)
        {
            InitializeComponent();
            roomName.Text = room.name;
            roomId.Text = room.id.ToString();
            questionAmount.Text = room.numOfQuestionsInGame.ToString();
            timePerQuestion.Text = $"{room.timePerQuestion} sec";
            byte[] request = Serializer.SearalizeGetPlayersInRoomRequest(room.id);
            byte[] response = MainWindow.communicator.sendAndReceive(request);
            List<string> players = Deserializer.DeserializeGetPlayersInRoomResponse(response);
            playersList.ItemsSource = players;
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
