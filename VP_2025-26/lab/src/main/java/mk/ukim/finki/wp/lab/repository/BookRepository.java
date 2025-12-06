package mk.ukim.finki.wp.lab.repository;

import mk.ukim.finki.wp.lab.model.Book;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface BookRepository extends JpaRepository<Book, Long>{
    List<Book> findAllByAuthor_Id(Long authorId);
    void deleteById(Long id);
    List<Book> findByTitleContainingIgnoreCaseAndAverageRatingGreaterThan(String title, Double rating);
    List<Book> findAllByOrderByAuthor_SurnameAsc();
}
