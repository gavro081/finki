import org.junit.jupiter.api.Nested;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import java.util.List;
import java.util.Optional;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.*;

@ExtendWith(MockitoExtension.class)
class CourseServiceTest {

    @Mock
    private CourseRepository courseRepository;

    @InjectMocks
    private CourseService courseService;

    @Nested
    class FindActiveCourses {

        @Test
        void returnsOnlyActiveCourses() {
            Course active = new Course(1L, "A", 6, true);
            Course inactive = new Course(2L, "B", 6, false);
            when(courseRepository.findAll()).thenReturn(List.of(active, inactive));

            List<Course> result = courseService.findActiveCourses();

            assertEquals(1, result.size());
            assertTrue(result.get(0).isActive());
            assertEquals("A", result.get(0).getName());
        }

        @Test
        void returnsEmptyList_whenNoCoursesExist() {
            when(courseRepository.findAll()).thenReturn(List.of());

            List<Course> result = courseService.findActiveCourses();

            assertTrue(result.isEmpty());
        }

        @Test
        void returnsEmptyList_whenAllCoursesAreInactive() {
            Course inactive1 = new Course(1L, "B", 3, false);
            Course inactive2 = new Course(2L, "C", 6, false);
            when(courseRepository.findAll()).thenReturn(List.of(inactive1, inactive2));

            List<Course> result = courseService.findActiveCourses();

            assertTrue(result.isEmpty());
        }

        @Test
        void returnsAllCourses_whenAllAreActive() {
            Course a = new Course(1L, "SP", 6, true);
            Course b = new Course(2L, "OOP", 6, true);
            when(courseRepository.findAll()).thenReturn(List.of(a, b));

            List<Course> result = courseService.findActiveCourses();

            assertEquals(2, result.size());
        }
    }

    @Nested
    class FindById {
        @Test
        void returnsCourse_whenFound() {
            Course course = new Course(1L, "SKIT", 6, true);
            when(courseRepository.findById(1L)).thenReturn(Optional.of(course));

            Course result = courseService.findById(1L);

            assertEquals(1L, result.getId());
            assertEquals("SKIT", result.getName());
        }

        @Test
        void throwsRuntimeException_whenNotFound() {
            when(courseRepository.findById(99L)).thenReturn(Optional.empty());

            RuntimeException ex = assertThrows(RuntimeException.class,
                    () -> courseService.findById(99L));

            assertEquals("Course not found", ex.getMessage());
        }
    }

    @Nested
    class CreateCourse {
        @Test
        void returnsSavedCourse_whenInputIsValid() {
            Course saved = new Course(1L, "PV", 2, true);
            when(courseRepository.save(any(Course.class))).thenReturn(saved);

            Course result = courseService.createCourse("PV", 2);

            assertNotNull(result);
            assertEquals("PV", result.getName());
            assertEquals(2, result.getCredits());
            assertTrue(result.isActive());
        }

        @Test
        void passesActiveCourseToPersistence_whenInputIsValid() {
            when(courseRepository.save(any(Course.class)))
                    .thenAnswer(invocation -> invocation.getArgument(0));

            Course result = courseService.createCourse("BiM", 6);

            assertTrue(result.isActive(), "Newly created course must be active");
            assertNull(result.getId(), "Id should be null before persistence assigns one");
            verify(courseRepository, times(1)).save(any(Course.class));
        }

        @Test
        void throwsIllegalArgumentException_whenNameIsNull() {
            IllegalArgumentException ex = assertThrows(IllegalArgumentException.class,
                    () -> courseService.createCourse(null, 3));

            assertEquals("Course name is required", ex.getMessage());
            verify(courseRepository, never()).save(any());
        }

        @Test
        void throwsIllegalArgumentException_whenNameIsBlank() {
            IllegalArgumentException ex = assertThrows(IllegalArgumentException.class,
                    () -> courseService.createCourse("   ", 3));

            assertEquals("Course name is required", ex.getMessage());
            verify(courseRepository, never()).save(any());
        }

        @Test
        void throwsIllegalArgumentException_whenNameIsEmpty() {
            IllegalArgumentException ex = assertThrows(IllegalArgumentException.class,
                    () -> courseService.createCourse("", 3));

            assertEquals("Course name is required", ex.getMessage());
            verify(courseRepository, never()).save(any());
        }

        @Test
        void throwsIllegalArgumentException_whenCreditsAreZero() {
            IllegalArgumentException ex = assertThrows(IllegalArgumentException.class,
                    () -> courseService.createCourse("VVKN", 0));

            assertEquals("Credits must be positive", ex.getMessage());
            verify(courseRepository, never()).save(any());
        }

        @Test
        void throwsIllegalArgumentException_whenCreditsAreNegative() {
            IllegalArgumentException ex = assertThrows(IllegalArgumentException.class,
                    () -> courseService.createCourse("VVKN", -5));

            assertEquals("Credits must be positive", ex.getMessage());
            verify(courseRepository, never()).save(any());
        }
    }

    @Nested
    class DeleteCourse {

        @Test
        void deletesCourse_whenCourseExists() {
            Course course = new Course(1L, "M2", 6, true);
            when(courseRepository.findById(1L)).thenReturn(Optional.of(course));

            courseService.deleteCourse(1L);

            verify(courseRepository, times(1)).deleteById(1L);
        }

        @Test
        void throwsRuntimeException_whenCourseDoesNotExist() {
            when(courseRepository.findById(99L)).thenReturn(Optional.empty());

            RuntimeException ex = assertThrows(RuntimeException.class,
                    () -> courseService.deleteCourse(99L));

            assertEquals("Course not found", ex.getMessage());
            verify(courseRepository, never()).deleteById(any());
        }

        @Test
        void usesIdFromRetrievedCourse_whenDeleting() {
            Course course = new Course(42L, "OOAID", 6, true);
            when(courseRepository.findById(42L)).thenReturn(Optional.of(course));

            courseService.deleteCourse(42L);

            verify(courseRepository).deleteById(42L);
        }
    }
}
