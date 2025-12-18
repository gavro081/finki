package mk.ukim.finki.wp.kol2025g2.service.impl;

import mk.ukim.finki.wp.kol2025g2.model.SkiResort;
import mk.ukim.finki.wp.kol2025g2.repository.SkiResortRepository;
import mk.ukim.finki.wp.kol2025g2.service.SkiResortService;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class SkiResortServiceImpl implements SkiResortService {
    private final SkiResortRepository repository;

    public SkiResortServiceImpl(SkiResortRepository repository) {
        this.repository = repository;
    }

    @Override
    public SkiResort findById(Long id) {
        return repository.findById(id).get();
    }

    @Override
    public List<SkiResort> listAll() {
        return repository.findAll();
    }

    @Override
    public SkiResort create(String name, String location) {
        SkiResort skiResort = new SkiResort(name, location);
        repository.save(skiResort);
        return skiResort;
    }
}
