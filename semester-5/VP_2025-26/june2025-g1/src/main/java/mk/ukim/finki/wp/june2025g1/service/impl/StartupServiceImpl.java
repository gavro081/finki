package mk.ukim.finki.wp.june2025g1.service.impl;

import lombok.AllArgsConstructor;
import mk.ukim.finki.wp.june2025g1.model.Founder;
import mk.ukim.finki.wp.june2025g1.model.Industry;
import mk.ukim.finki.wp.june2025g1.model.Startup;
import mk.ukim.finki.wp.june2025g1.model.exceptions.InvalidStartupIdException;
import mk.ukim.finki.wp.june2025g1.repository.StartupRepository;
import mk.ukim.finki.wp.june2025g1.service.FounderService;
import mk.ukim.finki.wp.june2025g1.service.StartupService;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.jpa.domain.Specification;
import org.springframework.stereotype.Service;

import java.util.List;

import static mk.ukim.finki.wp.june2025g1.service.specifications.FieldFilterSpecification.*;

@Service
@AllArgsConstructor
public class StartupServiceImpl implements StartupService {
    private final StartupRepository repository;
    private final FounderService founderService;

    @Override
    public List<Startup> listAll() {
        return repository.findAll();
    }

    @Override
    public Startup findById(Long id) {
        return repository.findById(id).orElseThrow(InvalidStartupIdException::new);
    }

    @Override
    public Startup create(String name, Double valuation, Integer yearFounded, Industry industry, Long founderId) {
        Founder founder = founderService.findById(founderId);
        return repository.save(new Startup(name, valuation, yearFounded, industry, founder));
    }

    @Override
    public Startup update(Long id, String name, Double valuation, Integer yearFounded, Industry industry, Long founderId) {
        Startup s = findById(id);
        s.setName(name);
        s.setFounder(founderService.findById(founderId));
        s.setIndustry(industry);
        s.setYearFounded(yearFounded);
        s.setValuation(valuation);
        return repository.save(s);
    }

    @Override
    public Startup delete(Long id) {
        Startup s = findById(id);
        repository.delete(s);
        return s;
    }

    @Override
    public Startup deactivate(Long id) {
        Startup s = findById(id);
        s.setActive(false);
        repository.save(s);
        return s;
    }

    @Override
    public Page<Startup> findPage(String name, Double valuation, Integer yearFounded, Industry industry, Long founderId, int pageNum, int pageSize) {
        Specification<Startup> specification = Specification.allOf(
                filterContainsText(Startup.class, "name", name),
                greaterThan(Startup.class, "valuation", valuation),
                greaterThan(Startup.class, "yearFounded", yearFounded),
                filterEqualsV(Startup.class, "industry", industry),
                filterEquals(Startup.class, "founder.id", founderId)
        );

        return repository.findAll(
                specification,
                PageRequest.of(pageNum, pageSize));
    }

}
