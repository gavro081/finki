//package labs.lab8;

import java.util.ArrayList;
import java.util.List;

class Song {
    private final String title;
    private final String artist;

    public Song(String title, String artist) {
        this.title = title;
        this.artist = artist;
    }

    @Override
    public String toString() {
        return "Song{" +
                "title=" + title +
                ", artist=" + artist +
                '}';
    }
}

class MP3Player {
    private List<Song> songs;
    private int currentSong;
    private boolean isPlaying;
    private boolean isStopped;

    MP3Player(List<Song> songs){
        this.songs = songs;
        currentSong = 0;
        isPlaying = false;
        isStopped = false;
    }

    @Override
    public String toString() {
        return "MP3Player{" +
                "currentSong = " + currentSong +
                ", songList = " + songs +
                '}';
    }

    public void pressPlay() {
        if (isPlaying){
            System.out.println("Song is already playing");
        } else {
            System.out.println("Song " + currentSong + " is playing");
            isPlaying = true;
            isStopped = false;
        }
    }

    public void printCurrentSong() {
        System.out.println(songs.get(currentSong));
    }

    public void pressFWD() {
        System.out.println("Forward...");
        isStopped = false;
        isPlaying = false;
        currentSong = (currentSong + 1) % songs.size();
    }

    public void pressStop() {
        if (isPlaying) {
            System.out.println("Song " + currentSong + " is paused");
            isPlaying = false;
            isStopped = false;
        } else if (isStopped) {
            System.out.println("Songs are already stopped");
        } else {
            System.out.println("Songs are stopped");
            currentSong = 0;
            isStopped = true;

        }
    }

    public void pressREW() {
        System.out.println("Reward...");
        isPlaying = false;
        isStopped = false;
        currentSong = (currentSong - 1 + songs.size()) % songs.size();
    }
}

public class PatternTest {
    public static void main(String args[]) {
        List<Song> listSongs = new ArrayList<Song>();
        listSongs.add(new Song("first-title", "first-artist"));
        listSongs.add(new Song("second-title", "second-artist"));
        listSongs.add(new Song("third-title", "third-artist"));
        listSongs.add(new Song("fourth-title", "fourth-artist"));
        listSongs.add(new Song("fifth-title", "fifth-artist"));
        MP3Player player = new MP3Player(listSongs);


        System.out.println(player.toString());
        System.out.println("First test");


        player.pressPlay();
        player.printCurrentSong();
        player.pressPlay();
        player.printCurrentSong();

        player.pressPlay();
        player.printCurrentSong();
        player.pressStop();
        player.printCurrentSong();

        player.pressPlay();
        player.printCurrentSong();
        player.pressFWD();
        player.printCurrentSong();

        player.pressPlay();
        player.printCurrentSong();
        player.pressREW();
        player.printCurrentSong();


        System.out.println(player.toString());
        System.out.println("Second test");


        player.pressStop();
        player.printCurrentSong();
        player.pressStop();
        player.printCurrentSong();

        player.pressStop();
        player.printCurrentSong();
        player.pressPlay();
        player.printCurrentSong();

        player.pressStop();
        player.printCurrentSong();
        player.pressFWD();
        player.printCurrentSong();

        player.pressStop();
        player.printCurrentSong();
        player.pressREW();
        player.printCurrentSong();


        System.out.println(player.toString());
        System.out.println("Third test");


        player.pressFWD();
        player.printCurrentSong();
        player.pressFWD();
        player.printCurrentSong();

        player.pressFWD();
        player.printCurrentSong();
        player.pressPlay();
        player.printCurrentSong();

        player.pressFWD();
        player.printCurrentSong();
        player.pressStop();
        player.printCurrentSong();

        player.pressFWD();
        player.printCurrentSong();
        player.pressREW();
        player.printCurrentSong();


        System.out.println(player.toString());
    }
}

//Vasiot kod ovde
