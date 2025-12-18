package mk.ukim.finki.wp.kol2025g2.web;

import jakarta.servlet.http.HttpServletRequest;
import mk.ukim.finki.wp.kol2025g2.model.SkiSlope;
import mk.ukim.finki.wp.kol2025g2.model.SlopeDifficulty;
import mk.ukim.finki.wp.kol2025g2.service.SkiResortService;
import mk.ukim.finki.wp.kol2025g2.service.SkiSlopeService;
import org.springframework.data.domain.Page;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

@Controller
public class SkiSlopeController {
    private final SkiSlopeService slopeService;
    private final SkiResortService resortService;
    private final UserDetailsService userDetailsService;

    public SkiSlopeController(SkiSlopeService slopeService, SkiResortService resortService, UserDetailsService userDetailsService) {
        this.slopeService = slopeService;
        this.resortService = resortService;
        this.userDetailsService = userDetailsService;
    }

    /**
     * This method should use the "list.html" template to display all ski slopes.
     * The method should be mapped on paths '/' and '/ski-slopes'.
     * The arguments that this method takes are optional and can be 'null'.
     * The filtered ski slopes that are the result of the call
     * findPage method from the SkiSlopeService should be displayed.
     * If you want to return a paginated result, you should also pass the page number and the page size as arguments.
     *
     * @param name       Filters ski slopes whose names contain the specified text.
     * @param length     Filters ski slopes longer than the specified length in meters.
     * @param difficulty Filters ski slopes matching the specified difficulty level.
     * @param skiResort  Filters ski slopes belonging to the specified ski center.
     * @param pageNum    The page number
     * @param pageSize   The number of items per page
     * @return The view "list.html".
     */

    @GetMapping(value = {"/", "/ski-slopes"})
    public String listAll(@RequestParam(required = false) String name,
                          @RequestParam(required = false) Integer length,
                          @RequestParam(required = false) SlopeDifficulty difficulty,
                          @RequestParam(required = false) Long skiResort,
                          @RequestParam(defaultValue = "1") Integer pageNum,
                          @RequestParam(defaultValue = "10") Integer pageSize,
                          Model model) {
        Page<SkiSlope> page = slopeService.findPage(name, length, difficulty, skiResort, pageNum - 1, pageSize);
        model.addAttribute("skiSlopes", page);
        model.addAttribute("resorts", resortService.listAll());
        model.addAttribute("difficulties", SlopeDifficulty.values());
        return "list";
    }

    /**
     * This method should display the "form.html" template.
     * The method should be mapped on path '/ski-slopes/add'.
     *
     * @return The view "form.html".
     */
    @GetMapping("/ski-slopes/add")
    public String showAdd(Model model) {
        model.addAttribute("difficulties", SlopeDifficulty.values());
        model.addAttribute("resorts", resortService.listAll());
        return "form";
    }

    /**
     * This method should display the "form.html" template.
     * However, in this case, all 'input' elements should be filled with the appropriate value for the ski slope that is updated.
     * The method should be mapped on path '/ski-slopes/edit/[id]'.
     *
     * @return The view "form.html".
     */
    @GetMapping("/ski-slopes/edit/{id}")
    public String showEdit(@PathVariable Long id, Model model) {
        SkiSlope slope = slopeService.findById(id);
        model.addAttribute("length", slope.getLength());
        model.addAttribute("id", slope.getId());
        model.addAttribute("difficulty", slope.getDifficulty());
        model.addAttribute("name", slope.getName());
        model.addAttribute("skiResort", slope.getSkiResort());

        model.addAttribute("resorts", resortService.listAll());
        model.addAttribute("difficulties", SlopeDifficulty.values());
        return "form";
    }

    /**
     * This method should create a ski slope given the arguments it takes.
     * The method should be mapped on path '/ski-slopes'.
     * After the ski slope is created, all ski slopes should be displayed.
     *
     * @return The view "list.html".
     */
    @PostMapping("/ski-slopes")
    public String create(@RequestParam String name,
                         @RequestParam Integer length,
                         @RequestParam SlopeDifficulty difficulty,
                         @RequestParam Long skiResort) {
        slopeService.create(name, length, difficulty, skiResort);
        return "redirect:/ski-slopes";
    }

    /**
     * This method should update a ski slope given the arguments it takes.
     * The method should be mapped on path '/ski-slopes/[id]'.
     * After the ski slope is updated, all ski slopes should be displayed.
     *
     * @return The view "list.html".
     */
    @PostMapping("/ski-slopes/{id}")
    public String update(@PathVariable Long id, String name, Integer length, SlopeDifficulty difficulty, Long skiResort){
        slopeService.update(id, name, length, difficulty, skiResort);
        return "redirect:/ski-slopes";
    }

    @PostMapping
    public String login(@RequestParam String username,
                        @RequestParam String password,
                        HttpServletRequest req) {

        UserDetails userDetails = userDetailsService.loadUserByUsername(username);
        if (userDetails != null && userDetails.getPassword().equals(password)){
            req.getSession().setAttribute("userDetails", userDetails);
        }
        System.out.println(userDetails);

        return "redirect:/ski-slopes";
    }


    @PostMapping("/ski-slopes/delete/{id}")
    public String delete(@PathVariable Long id){
        slopeService.delete(id);
        return "redirect:/ski-slopes";
    }

    @PostMapping("/ski-slopes/close/{id}")
    public String close(@PathVariable Long id){
        slopeService.close(id);
        return "redirect:/ski-slopes";
    }
}