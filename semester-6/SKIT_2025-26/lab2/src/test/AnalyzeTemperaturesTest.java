package test;

import main.AnalyzeTemperaturesClass;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

public class AnalyzeTemperaturesTest {
    @Test
    void testCase1(){
        var out = AnalyzeTemperaturesClass.analyzeTemperatures(new int[]{-52});
        Assertions.assertEquals("Invalid temperatures detected.", out);
    }

    @Test
    void testCase2(){
        var out = AnalyzeTemperaturesClass.analyzeTemperatures(new int[]{13});
        Assertions.assertEquals("No warm days.", out);
    }

    @Test
    void testCase3(){
        var out = AnalyzeTemperaturesClass.analyzeTemperatures(new int[]{});
        Assertions.assertEquals("No warm days.", out);
    }

    @Test
    void testCase4(){
        var out = AnalyzeTemperaturesClass.analyzeTemperatures(new int[]{23,25});
        Assertions.assertEquals("All days were warm.", out);
    }

    @Test
    void testCase5(){
        var out = AnalyzeTemperaturesClass.analyzeTemperatures(new int[]{19,24});
        Assertions.assertEquals("Some days were warm.", out);
    }

    @Test
    void testCase6(){
        var out = AnalyzeTemperaturesClass.analyzeTemperatures(new int[]{-52,1,2,30});
        Assertions.assertEquals("Invalid temperatures detected.", out);
    }
}
