//package mk.ukim.finki.wp.lab.repository.impl;
//
//import mk.ukim.finki.wp.lab.bootstrap.DataHolder;
//import mk.ukim.finki.wp.lab.model.Author;
//import mk.ukim.finki.wp.lab.model.Book;
//import mk.ukim.finki.wp.lab.repository.BookRepository;
//import org.springframework.stereotype.Repository;
//
//import java.util.List;
//
//@Repository
//public class InMemoryBookRepository implements BookRepository {
//    @Override
//    public List<Book> findAll() {
//        return DataHolder.books;
//    }
//
//    @Override
//    public List<Book> searchBooks(String text, Double rating) {
//
//        return DataHolder.books.stream()
//                .filter(b -> b.getAverageRating() >= rating
//                        && b.getTitle().toLowerCase().contains(text.toLowerCase()))
//                .toList();
//    }
//
//    @Override
//    public boolean addBook(Book b) {
//        return DataHolder.books.add(b);
//    }
//
//    @Override
//    public boolean deleteBook(Long id) {
//        return DataHolder.books.removeIf(b -> b.getId().equals(id));
//    }
//
//    @Override
//    public Book getById(Long id) {
//        return DataHolder.books.stream()
//                .filter(b -> b.getId().equals(id))
//                .findFirst()
//                .orElse(null);
//    }
//
//    @Override
//    public Book save(Book b){
//        deleteBook(b.getId());
//        addBook(b);
//        return b;
//    }
//}
