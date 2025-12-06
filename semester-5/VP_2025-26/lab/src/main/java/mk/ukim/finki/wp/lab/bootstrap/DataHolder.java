package mk.ukim.finki.wp.lab.bootstrap;

import jakarta.annotation.PostConstruct;
import mk.ukim.finki.wp.lab.model.Author;
import mk.ukim.finki.wp.lab.model.Book;
import mk.ukim.finki.wp.lab.model.BookReservation;
import mk.ukim.finki.wp.lab.repository.AuthorRepository;
import mk.ukim.finki.wp.lab.repository.BookRepository;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

@Component
public class DataHolder {
    private final BookRepository bookRepository;
    private final AuthorRepository authorRepository;

    public DataHolder(BookRepository bookRepository, AuthorRepository authorRepository) {
        this.bookRepository = bookRepository;
        this.authorRepository = authorRepository;
    }

    public static List<Book> books = new ArrayList<>();
    public static List<BookReservation> reservations = new ArrayList<>();
    public static List<Author> authors = List.of(
            new Author("filip", "gavrilovski",
                    "MK", "lorem ipsum"),
            new Author("aleksandar", "gavrilovski",
                    "MK", "ipsum lorem"),
            new Author("dimi", "arsov",
                    "MK", "nz")
    );
    @PostConstruct
    public void init(){
        Random random = new Random();
        String []genres = new String[]{"comedy", "romance", "drama"};
        String []names = new String[]{"name", "kniga", "book"};
        for (int i = 0; i < 10; i++) {
            int nameIndex = random.nextInt(3);
            int genreIndex = random.nextInt(3);
            int authorIndex = random.nextInt(3);
            double rand = random.nextDouble() * 10;
            double rating = Math.round(rand * 100.0) / 100.0;
            Book book = new Book(names[nameIndex] + i,
                    genres[genreIndex],
                    rating,
                    authors.get(authorIndex));
            books.add(book);
        }
        if (authorRepository.findAll().isEmpty())
            authorRepository.saveAll(authors);
        if (bookRepository.findAll().isEmpty())
            bookRepository.saveAll(books);
    }
}
