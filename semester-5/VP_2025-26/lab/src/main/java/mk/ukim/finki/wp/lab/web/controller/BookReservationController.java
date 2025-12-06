package mk.ukim.finki.wp.lab.web.controller;

import jakarta.servlet.http.HttpServletRequest;
import mk.ukim.finki.wp.lab.model.Book;
import mk.ukim.finki.wp.lab.service.BookReservationService;
import mk.ukim.finki.wp.lab.service.BookService;
import mk.ukim.finki.wp.lab.service.impl.BookReservationServiceImpl;
import mk.ukim.finki.wp.lab.service.impl.BookServiceImpl;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
@RequestMapping("/bookReservation")
public class BookReservationController {
    private final BookReservationService bookReservationService;
    private final BookService bookService;

    public BookReservationController(BookReservationServiceImpl bookReservationService, BookServiceImpl bookService) {
        this.bookReservationService = bookReservationService;
        this.bookService = bookService;
    }

    @PostMapping
    public String makeReservation(
            @RequestParam String bookTitle,
            @RequestParam String readerName,
            @RequestParam String readerAddress,
            @RequestParam String numCopies,
            HttpServletRequest request,
            Model model) {

        model.addAttribute("bookTitle",bookTitle);
        model.addAttribute("readerName",readerName);
        model.addAttribute("readerAddress",readerAddress);
        model.addAttribute("numCopies",numCopies);

        model.addAttribute("ipAddress", request.getRemoteAddr());
        Book book = bookService.searchBooks(bookTitle, 0.0).get(0);
        bookReservationService.placeReservation(book, readerName, readerAddress, Integer.parseInt(numCopies));
        return "reservationConfirmation";

    }

}
