package mk.ukim.finki.wp.june2025g1.service.impl;

import lombok.AllArgsConstructor;
import mk.ukim.finki.wp.june2025g1.model.Founder;
import mk.ukim.finki.wp.june2025g1.model.exceptions.InvalidFounderIdException;
import mk.ukim.finki.wp.june2025g1.repository.FounderRepository;
import mk.ukim.finki.wp.june2025g1.service.FounderService;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
@AllArgsConstructor
public class FounderServiceImpl implements FounderService {
    private final FounderRepository repository;
    @Override
    public Founder findById(Long id) {
        return repository.findById(id).orElseThrow(InvalidFounderIdException::new);
    }

    @Override
    public List<Founder> listAll() {
        return repository.findAll();
    }

    @Override
    public Founder create(String name, String email) {
        return repository.save(new Founder(name, email));
    }
}
