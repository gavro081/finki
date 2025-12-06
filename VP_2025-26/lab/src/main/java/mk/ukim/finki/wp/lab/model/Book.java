package mk.ukim.finki.wp.lab.model;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Entity
@AllArgsConstructor
@Setter
@NoArgsConstructor
@Table(name = "books")
public class Book {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String title;
    private String genre;
    private double averageRating;

    @ManyToOne
    @JoinColumn(name = "authors.id")
    private Author author;

    public Book(String s, String genre, double rating, Author author) {
        this.title = s;
        this.genre = genre;
        this.averageRating = rating;
        this.author = author;
    }

    @Override
    public String toString() {
        return "Title: " + title +
                ", Genre: " + genre +
                ", Rating: " + averageRating +
                ", Author: " + author.toString();
    }
}
