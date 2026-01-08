package mk.ukim.finki.wp.jan2025g2.service.impl;

import lombok.AllArgsConstructor;
import mk.ukim.finki.wp.jan2025g2.model.NationalPark;
import mk.ukim.finki.wp.jan2025g2.model.ParkLocation;
import mk.ukim.finki.wp.jan2025g2.model.ParkType;
import mk.ukim.finki.wp.jan2025g2.model.exceptions.InvalidNationalParkIdException;
import mk.ukim.finki.wp.jan2025g2.repository.NationalParkRepository;
import mk.ukim.finki.wp.jan2025g2.service.NationalParkService;
import mk.ukim.finki.wp.jan2025g2.service.ParkLocationService;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.jpa.domain.Specification;
import org.springframework.stereotype.Service;

import java.util.List;

import static mk.ukim.finki.wp.jan2025g2.service.FieldFilterSpecification.*;

@Service
@AllArgsConstructor
public class NationalParkServiceImpl implements NationalParkService {
    private final NationalParkRepository nationalParkRepository;
    private final ParkLocationService service;

    @Override
    public List<NationalPark> listAll() {
        return nationalParkRepository.findAll();
    }

    @Override
    public NationalPark findById(Long id) {
        return nationalParkRepository.findById(id).orElseThrow(InvalidNationalParkIdException::new);
    }

    @Override
    public NationalPark create(String name, Double areaSize, Double rating, ParkType parkType, Long locationId) {
        ParkLocation location = service.findById(locationId);
        return nationalParkRepository.save(new NationalPark(name, areaSize, rating, parkType, location));
    }

    @Override
    public NationalPark update(Long id, String name, Double areaSize, Double rating, ParkType parkType, Long locationId) {
        NationalPark park = findById(id);
        park.setName(name);
        park.setAreaSize(areaSize);
        park.setRating(rating);
        park.setParkType(parkType);
        park.setLocation(service.findById(locationId));
        return nationalParkRepository.save(park);
    }

    @Override
    public NationalPark delete(Long id) {
        NationalPark park = findById(id);
        nationalParkRepository.delete(park);
        return park;
    }

    @Override
    public NationalPark close(Long id) {
        NationalPark park = findById(id);
        park.setClosed(true);
        nationalParkRepository.save(park);
        return park;
    }

    @Override
    public Page<NationalPark> findPage(String name, Double areaSize, Double rating, ParkType parkType, Long locationId, int pageNum, int pageSize) {
        Specification<NationalPark> specification = Specification.allOf(
                filterContainsText(NationalPark.class, "name", name),
                greaterThan(NationalPark.class, "areaSize", areaSize),
                greaterThan(NationalPark.class, "rating", rating),
                filterEqualsV(NationalPark.class, "parkType", parkType),
                filterEquals(NationalPark.class, "location.id", locationId)
        );

        return this.nationalParkRepository.findAll(
                specification,
                PageRequest.of(pageNum, pageSize));
    }
}
