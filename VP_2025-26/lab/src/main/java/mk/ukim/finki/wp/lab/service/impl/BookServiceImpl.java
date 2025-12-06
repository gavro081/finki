package mk.ukim.finki.wp.lab.service.impl;

import mk.ukim.finki.wp.lab.model.Author;
import mk.ukim.finki.wp.lab.model.Book;
import mk.ukim.finki.wp.lab.repository.BookRepository;
import mk.ukim.finki.wp.lab.service.BookService;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class BookServiceImpl implements BookService {
    private final BookRepository bookRepository;

    public BookServiceImpl(BookRepository bookRepository) {
        this.bookRepository = bookRepository;
    }

    @Override
    public List<Book> listAll() {
        return bookRepository.findAll();
    }

    @Override
    public List<Book> searchBooks(String text, Double rating) {
        return bookRepository.findByTitleContainingIgnoreCaseAndAverageRatingGreaterThan(text, rating);
    }

    @Override
    public boolean addBook(String title, String genre, Double rating, Author author) {
        // check for nulls
        bookRepository.save(new Book(title,genre,rating, author));
        return true;
    }

    @Override
    public boolean deleteBook(Long id) {
        bookRepository.deleteById(id);
        return true;
    }

    @Override
    public Book getById(Long id) {
        return bookRepository.findById(id).orElse(null);
    }

    @Override
    public void editBook(Long bookId, String title, String genre, Double averageRating, Author author) {
        Book book = getById(bookId);
        book.setTitle(title);
        book.setGenre(genre);
        book.setAverageRating(averageRating);
        book.setAuthor(author);
        bookRepository.save(book);
    }

    @Override
    public List<Book> listAllSorted() {
        return bookRepository.findAllByOrderByAuthor_SurnameAsc();
    }
}
