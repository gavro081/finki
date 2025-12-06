package mk.ukim.finki.wp.lab.service.impl;

import mk.ukim.finki.wp.lab.model.Author;
import mk.ukim.finki.wp.lab.repository.AuthorRepository;
import mk.ukim.finki.wp.lab.service.AuthorService;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class AuthorServiceImpl implements AuthorService {
    private final AuthorRepository authorRepository;

    public AuthorServiceImpl(AuthorRepository authorRepository) {
        this.authorRepository = authorRepository;
    }

    @Override
    public List<Author> findAll() {
        return authorRepository.findAllByOrderByNameDesc();
    }

    @Override
    public Author findByID(Long id) {
        return authorRepository.findById(id).orElse(null);
    }

    @Override
    public void incrementLikesByAuthor(Long id) {
        Author author = authorRepository.getAuthorById(id);
        author.setLikes(author.getLikes() + 1);
        authorRepository.save(author);
    }
}
