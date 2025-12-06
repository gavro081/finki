package mk.ukim.finki.wp.lab.service;

import mk.ukim.finki.wp.lab.model.Book;
import mk.ukim.finki.wp.lab.model.BookReservation;

public interface BookReservationService {
    BookReservation placeReservation(Book book, String readerName, String readerAddress, int numberOfCopies);
}
