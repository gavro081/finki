package mk.ukim.finki.wp.lab.service;

import mk.ukim.finki.wp.lab.model.Author;
import mk.ukim.finki.wp.lab.model.Book;

import java.util.List;

public interface BookService {
    List<Book> listAll();
    List<Book> listAllSorted();
    List<Book> searchBooks(String text, Double rating);
    boolean addBook(String title, String genre, Double rating, Author author);
    boolean deleteBook(Long id);
    Book getById(Long id);
    void editBook(Long bookId, String title, String genre, Double averageRating, Author author);
}