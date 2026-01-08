package mk.ukim.finki.wp.jan2025g2.service.impl;

import lombok.AllArgsConstructor;
import mk.ukim.finki.wp.jan2025g2.model.ParkLocation;
import mk.ukim.finki.wp.jan2025g2.model.exceptions.InvalidParkLocationIdException;
import mk.ukim.finki.wp.jan2025g2.repository.ParkLocationRepository;
import mk.ukim.finki.wp.jan2025g2.service.ParkLocationService;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
@AllArgsConstructor
public class ParkLocationServiceImpl implements ParkLocationService {
    private final ParkLocationRepository repository;
    @Override
    public ParkLocation findById(Long id) {
        return repository.findById(id).orElseThrow(InvalidParkLocationIdException::new);
    }

    @Override
    public List<ParkLocation> listAll() {
        return repository.findAll();
    }

    @Override
    public ParkLocation create(String country, String continent) {
        return repository.save(new ParkLocation(country, continent));
    }
}
