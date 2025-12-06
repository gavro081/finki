package mk.ukim.finki.wp.lab.repository;

import mk.ukim.finki.wp.lab.model.Author;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;


@Repository
public interface AuthorRepository extends JpaRepository<Author, Long> {
    Author getAuthorById(Long id);
    List<Author> findAllByOrderByNameDesc();
//    public List<Author> findAll();
//    public Author getById(Long id);
//    public void incrementLikesById(Long id);
}
