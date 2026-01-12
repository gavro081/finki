package mk.ukim.finki.wp.kol2025g2.service.impl;

import lombok.AllArgsConstructor;
import mk.ukim.finki.wp.kol2025g2.model.SkiSlope;
import mk.ukim.finki.wp.kol2025g2.model.SlopeDifficulty;
import mk.ukim.finki.wp.kol2025g2.repository.SkiSlopeRepository;
import mk.ukim.finki.wp.kol2025g2.service.SkiResortService;
import mk.ukim.finki.wp.kol2025g2.service.SkiSlopeService;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.jpa.domain.Specification;
import org.springframework.stereotype.Service;

import java.util.List;

import static mk.ukim.finki.wp.kol2025g2.service.FieldFilterSpecification.*;

@Service
@AllArgsConstructor
public class SkiSlopeServiceImpl implements SkiSlopeService {
    private final SkiSlopeRepository repository;
    private final SkiResortService service;

    @Override
    public List<SkiSlope> listAll() {
        return repository.findAll();
    }

    @Override
    public SkiSlope findById(Long id) {
        return repository.findById(id).get();
    }

    @Override
    public SkiSlope create(String name, Integer length, SlopeDifficulty difficulty, Long skiResort) {
        return repository.save(new SkiSlope(name, length, difficulty, service.findById(skiResort)));
    }

    @Override
    public SkiSlope update(Long id, String name, Integer length, SlopeDifficulty difficulty, Long skiResort) {
        SkiSlope skiSlope = findById(id);
        skiSlope.setSkiResort(service.findById(skiResort));
        skiSlope.setName(name);
        skiSlope.setDifficulty(difficulty);
        skiSlope.setLength(length);
        return repository.save(skiSlope);
    }

    @Override
    public SkiSlope delete(Long id) {
        SkiSlope s = findById(id);
        repository.delete(s);
        return s;
    }

    @Override
    public SkiSlope close(Long id) {
        SkiSlope s = findById(id);
        s.close();
        return repository.save(s);
    }

    @Override
    public Page<SkiSlope> findPage(String name, Integer length, SlopeDifficulty difficulty, Long skiResort, int pageNum, int pageSize) {
        Specification<SkiSlope> specification = Specification.allOf(
                filterContainsText(SkiSlope.class, "name", name),
                greaterThan(SkiSlope.class, "length", length),
                filterEquals(SkiSlope.class, "skiResort.id", skiResort),
                filterEqualsV(SkiSlope.class, "difficulty", difficulty)
        );

        return this.repository.findAll(
                specification,
                PageRequest.of(pageNum, pageSize)
        );
    }
}
