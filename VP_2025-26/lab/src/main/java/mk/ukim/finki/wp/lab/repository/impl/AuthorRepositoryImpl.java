//package mk.ukim.finki.wp.lab.repository.impl;
//
//import mk.ukim.finki.wp.lab.model.Author;
//import mk.ukim.finki.wp.lab.repository.AuthorRepository;
//import org.springframework.stereotype.Repository;
//
//import java.util.List;
//
//import static mk.ukim.finki.wp.lab.bootstrap.DataHolder.authors;
//
//@Repository
//public class AuthorRepositoryImpl implements AuthorRepository {
//    @Override
//    public List<Author> findAll() {
//        return authors;
//    }
//
//    @Override
//    public Author getById(Long id) {
//        return authors.stream()
//                .filter(author -> author.getId().equals(id))
//                .findFirst()
//                .orElse(null);
//    }
//
////    @Override
//    public void incrementLikesById(Long id){
//        Author author = getById(id);
//        author.setLikes(author.getLikes() + 1);
//    }
//}
