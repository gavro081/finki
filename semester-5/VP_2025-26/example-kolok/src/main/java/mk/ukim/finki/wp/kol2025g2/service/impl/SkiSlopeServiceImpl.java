package mk.ukim.finki.wp.kol2025g2.service.impl;

import mk.ukim.finki.wp.kol2025g2.model.SkiSlope;
import mk.ukim.finki.wp.kol2025g2.model.SlopeDifficulty;
import mk.ukim.finki.wp.kol2025g2.repository.SkiResortRepository;
import mk.ukim.finki.wp.kol2025g2.repository.SkiSlopeRepository;
import mk.ukim.finki.wp.kol2025g2.service.SkiSlopeService;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.jpa.domain.Specification;
import org.springframework.stereotype.Service;
import static mk.ukim.finki.wp.kol2025g2.service.FieldFilterSpecification.*;

import java.util.List;

@Service
public class SkiSlopeServiceImpl implements SkiSlopeService {
   private final SkiSlopeRepository skiSlopeRepository;
   private final SkiResortRepository skiResortRepository;

    public SkiSlopeServiceImpl(SkiSlopeRepository skiSlopeRepository, SkiResortRepository skiResortRepository) {
        this.skiSlopeRepository = skiSlopeRepository;
        this.skiResortRepository = skiResortRepository;
    }

    @Override
    public List<SkiSlope> listAll() {
        return skiSlopeRepository.findAll();
    }

    @Override
    public SkiSlope findById(Long id) {
        return skiSlopeRepository.findById(id).get();
    }

    @Override
    public SkiSlope create(String name, Integer length, SlopeDifficulty difficulty, Long skiResort) {
        SkiSlope entity = new SkiSlope(name, length, difficulty, skiResortRepository.findById(skiResort).get());
        return skiSlopeRepository.save(entity);
    }

    @Override
    public SkiSlope update(Long id, String name, Integer length, SlopeDifficulty difficulty, Long skiResort) {
        SkiSlope skiSlope = skiSlopeRepository.findById(id).get();
        skiSlope.setName(name);
        skiSlope.setSkiResort(skiResortRepository.findById(skiResort).get());
        skiSlope.setLength(length);
        skiSlope.setDifficulty(difficulty);
        skiSlopeRepository.save(skiSlope);
        return skiSlope;
    }

    @Override
    public SkiSlope delete(Long id) {
        SkiSlope skiSlope = skiSlopeRepository.findById(id).get();
        skiSlopeRepository.delete(skiSlope);
        return skiSlope;
    }

    @Override
    public SkiSlope close(Long id) {
        SkiSlope skiSlope = skiSlopeRepository.findById(id).get();
        skiSlope.setClosed(true);
        skiSlopeRepository.save(skiSlope);
        return skiSlope;
    }

    @Override
    public Page<SkiSlope> findPage(String name, Integer length, SlopeDifficulty difficulty, Long skiResort, int pageNum, int pageSize) {

        Specification<SkiSlope> specification = Specification.allOf(
                filterContainsText(SkiSlope.class, "name", name),
                greaterThan(SkiSlope.class, "length", length),
                filterEqualsV(SkiSlope.class, "difficulty", difficulty),
                filterEquals(SkiSlope.class, "skiResort.id", skiResort)
        );

        return skiSlopeRepository.findAll(
                specification,
                PageRequest.of(pageNum, pageSize)
        );
    }
}
