#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

  // SECTION 1 - READING IN FILE

  FILE *fp; // declare a file

  fp = fopen("statscan_diabetes.csv",
             "r"); // opens the diabetes file for reading

  if (fp ==
      NULL) { // if the code isn't somehow able to find the file or it fails to
              // find it, it'll print an error and exit the program

    printf("Error in loading in data file");
    return 0; // exits the program
  }

  // EVERY VARIABLE THAT I USED HAS BEEN DECLARED HERE, SO DO NOT REUSE THE SAME
  // NAMES BY MISTAKE
  char line[200]; // string variable that will hold store each line of the file
                  // as the reader goes line by line
  char *token;    // this variable will be used to split each line into seperate
               // strings in order to store them as seperate array values into
               // the same index value at the same row
  int year[209]; // array that stores year for each row i into the index i of
                 // the array
  int location[209]; // same idea for each of the arrays below
  int age[209];
  int sex[209];
  float percentage[209];
  int indexCounter = 0; // intialize the index counter to 0 (this will be used
                        // as the row value)

  fgets(line, sizeof(line), fp); // skips the header line of the CSV file

  while (fgets(line, sizeof(line), fp) !=
         NULL) { // loop that continues until every line has been read

    token = strtok(line, ",\""); // gets year and stores it in token

    // checks what year token is, and inputs an integer (from 0 to 6) into the
    // year array depending on which year it is
    if (!strcmp(token,
                "2015")) { // for example, if the year is 2015 in that row,
                           // store 0 into the array at the row number
      year[indexCounter] = 0;
      // printf("is 2015");
    } else if (!strcmp(token, "2016")) {
      year[indexCounter] = 1;
      // printf("is 2016");
    } else if (!strcmp(token, "2017")) {
      year[indexCounter] = 2;
      // printf("is 2017");

    } else if (!strcmp(token, "2018")) {
      year[indexCounter] = 3;
      // printf("is 2018");
    } else if (!strcmp(token, "2019")) {
      // printf("is 2019");
      year[indexCounter] = 4;
    } else if (!strcmp(token, "2020")) {
      // printf("is 2020");
      year[indexCounter] = 5;
    } else if (!strcmp(token, "2021")) {
      // printf("is 2021");
      year[indexCounter] = 6;
    }

    token = strtok(
        NULL, ",\""); // gets location  and stores an integer (0 to 4) value
                      // into location array depending on what location it is

    if (!strcmp(
            token,
            "Canada (excluding territories)")) { // for example, if the location
                                                 // is canada in the row, store
                                                 // 0 into the array of that row
      location[indexCounter] = 0;
    } else if (!strcmp(token, "Quebec")) {
      location[indexCounter] = 1;
    } else if (!strcmp(token, "Ontario")) {
      location[indexCounter] = 2;
    } else if (!strcmp(token, "Alberta")) {
      location[indexCounter] = 3;
    } else if (!strcmp(token, "British Columbia")) {
      location[indexCounter] = 4;
    }

    token = strtok(NULL, ",,"); // SKIPS GNUID

    token =
        strtok(NULL, ",\""); // gets age, and stores an int value (0 to 2) into
                             // age array depending on what age group it is

    if (!strcmp(token, "35 to 49 years")) {
      age[indexCounter] = 0;
    } else if (!strcmp(token, "50 to 64 years")) {
      age[indexCounter] = 1;
    } else if (!strcmp(token, "65 years and over")) {
      age[indexCounter] = 2;
    }

    token = strtok(NULL, ",\""); // gets sex, and stores int value either 0 (for
                                 // male) or 1 (for female) into sex array

    if (!strcmp(token, "Males")) {
      sex[indexCounter] = 0;
    } else if (!strcmp(token, "Females")) {
      sex[indexCounter] = 1;
    }

    token = strtok(NULL, "\"Diabetes\",\"Percent\",\"Percent\",\"239\","
                         "\"units\",\"0\","); // skips something

    token = strtok(NULL, ",\""); // skips something

    token = strtok(NULL, ","); // skips coordinates

    token =
        strtok(NULL, "\""); // gets percetage value, and stores 0 into the array
                            // if it was empty in the data, otherwise store the
                            // percentage as a float into the array

    if (!strcmp(token, ",")) {
      percentage[indexCounter] = 0; // NOTE, 0 MEANS THAT THE DATA WAS MISSING
                                    // IN THE CHART, NOT THAT PERCENTAGE IS 0
    } else { // convert the string to a float, and put that into the array from
             // the corresponding row
      percentage[indexCounter] = atof(token);
    }
    indexCounter++; // increase the index counter for the next loop iteration

    if (indexCounter == 210) { // if the index counter goes beyond the amount of
                               // rows, end the loop
      break;
    }

  } // loop ends here

  /*NOTES FROM NADIF ABOUT HOW THE ARRAYS WORK

   - There are 210 rows from the data (excluding the first header row), so each
  array goes from index 0 to 209 and has 210 elements.
   - Each index value for each array corresponds to the same row, for example
  sex[45] and percentage[45] are both on the 46th row from the data  (not
  including the heading file)

      - for the arrays year[i], location[i], age[i], sex[i], they are integer
  arrays where each integer means some quality. Below is what each integer value
  means for each array

       year[i] value:
       0 ---> 2015, 1 -----> 2016, 2 -----> 2017, 3 -----> 2018, 4 ------> 2019,
  5 ------> 2020, 6 -----> 2021

       location[i] array:
       0 ---> Canada (excluding terr.), 1 ---> Quebec, 2 ---> Ontario, 3 --->
  Alberta, 4 ---> British Columbia

       age[i] array value:

       0 ---> 35 to 49 years, 1 ---> 50 to 64 years, 2 ---> 65 years and over

       sex[i] array value:

       0 ---> Males
       1 ---> Females

       For the percentage array, the value of percetange[i] is a float value
  which is simply the percentage as seen from the data

       HOWEVER, VERY IMPORTANT DETAIL** ----> If the percentage is 0, THIS DOES
  NOT MEAN 0 PEOPLE  DIAGNOSED, it means THE VALUE WAS MISSING in the graph,
  **So it needs to be passed by in the calculations done in sections 2 and 3

  If you have any questions ask me
  */

  // if you wanna test the arrays, uncomment the bottom

  /*
   printf("YEAR    LOCATION     AGE         SEX     PERCENTAGE");
  for (int i = 0; i < 210; i++) {
               printf("\n%d        %d          %d             %d         %.2f",
      year[i], location[i], age[i], sex[i], percentage[i]);
       } */

  // SECTION 2 - CALCULATIONS

  printf("\n\n\n-----------------------------------------------------\n");
  printf("-----------------------------------------------------\n\n\n");

  // 1 A

  double provincialAverages[5]; //*** contains each provincial average(index
                                //1,2,3,4) and canada exc terretories (index 0)

  printf("Provincial Averages:\n");
  printf("\n\nProvice\t\t\t\tAverage %%");

  char places[][40] = {"Canada (excluding territories)", "Quebec", "Ontario",
                       "Alberta", "British Columbia"};
  double averages[5];

  for (int j = 1; j < 5; j++) {
    double total = 0;
    int divider = 0;
    for (int i = 0; i < 210; i++) {
      if (location[i] == j && percentage[i] != 0) {
        divider++;
        total += percentage[i];
      }
    }
    double average = total / divider;
    provincialAverages[j] = average;
  }

  for (int i = 1; i < 4; i++) {
    printf("\n%s\t\t\t\t%3lf%%", places[i], provincialAverages[i]);
  }
  printf("\n%s\t%.3lf%%", places[4], provincialAverages[4]);

  printf("\n\n\n-----------------------------------------------------\n\n\n");

  // 1 B
  double total = 0;
  int divider = 0;
  for (int i = 0; i < 210; i++) {
    if (location[i] == 0 && percentage[i] != 0) {
      divider++;
      total += percentage[i];
    }
  }
  double nAvg = total / divider;
  provincialAverages[0] = nAvg;
  printf("\nThe National Average is %.3lf %%", nAvg);

  printf("\n\n\n-----------------------------------------------------\n\n\n");

  // 1 C
  printf("\n\nYearly Averages:");
  int years[] = {2015, 2016, 2017, 2018, 2019, 2020, 2021};
  double highest = 0, lowest = 20;
  int highestYear, lowestYear;
  char highestPlace[20], lowestPlace[20];
  double YearAverages[7];

  for (int h = 1; h < 5; h++) {
    printf("\n\n%s:", places[h]);
    printf("\nYear\t\tAverage %%");
    for (int j = 0; j < 7; j++) {
      double total = 0;
      int divider = 0;
      for (int i = 0; i < 210; i++) {
        if (location[i] == h && year[i] == j && percentage[i] != 0) {
          divider++;
          total += percentage[i];
        }
      }
      double average = total / divider;
      if (average > highest) {
        highest = average;
        highestYear = years[j];
        strcpy(highestPlace, places[h]);
      }
      if (average < lowest) {
        lowest = average;
        lowestYear = years[j];
        strcpy(lowestPlace, places[h]);
      }
      printf("\n%d\t\t%.3lf", years[j], average);
    }
  }

  // national

  double yearlyprovincialAverages[7]; //*** contains the national average of
                                      //each year

  printf("\n\nNational Averages:");
  printf("\nYear\t\tAverage %%");

  for (int j = 0; j < 7; j++) {
    double total = 0;
    int divider = 0;
    for (int i = 0; i < 210; i++) {
      if (location[i] == 0 && year[i] == j && percentage[i] != 0) {
        divider++;
        total += percentage[i];
      }
    }
    nAvg = total / divider;
    yearlyprovincialAverages[j] = nAvg;
    printf("\n%d\t\t%.3lf", years[j], nAvg);
  }

  printf("\n\n\n-----------------------------------------------------\n\n\n");

  // 1 D

  printf("\n\nAge Group Averages:");
  char ageGroups[][10] = {"35-49", "50-64", "65+  "};

  for (int h = 1; h < 5; h++) {
    printf("\n\n%s:", places[h]);
    printf("\nAge Group\tAverage %%");
    for (int j = 0; j < 3; j++) {
      double total = 0;
      int divider = 0;
      for (int i = 0; i < 210; i++) {
        if (location[i] == h && age[i] == j && percentage[i] != 0) {
          divider++;
          total += percentage[i];
        }
      }
      double average = total / divider;
      printf("\n%s\t\t%.3lf", ageGroups[j], average);
    }
  }

  // National

  double nationalAgeAverages[3]; //*** This array contains the national averages
                                 //for all three age groups in order

  printf("\n\nNational Averages:");
  printf("\nAge Group\tAverage %%");

  for (int j = 0; j < 3; j++) {
    double total = 0;
    int divider = 0;
    for (int i = 0; i < 210; i++) {
      if (location[i] == 0 && age[i] == j && percentage[i] != 0) {
        divider++;
        total += percentage[i];
      }
    }
    double average = total / divider;
    nationalAgeAverages[j] = average;
    printf("\n%s\t\t%.3lf", ageGroups[j], average);
  }

  printf("\n\n\n-----------------------------------------------------\n");
  printf("-----------------------------------------------------\n\n\n");

  // 2

  double minAvg = 100;
  char lowestPercentage[40];
  double maxAvg = 0;
  char highestPercentage[40];

  for (int i = 1; i < 5; i++) { // scans the different provincial averages
    if (provincialAverages[i] < minAvg) { // finds minumum diabetes
      minAvg = provincialAverages[i];
      strcpy(lowestPercentage,
             places[(i)]); // stores the place corrosponding to the average
    }
    if (provincialAverages[i] > maxAvg) { // finds Maxiumum diabetes
      maxAvg = provincialAverages[i];
      strcpy(highestPercentage, places[(i)]);
    }
  }

  printf("\nThe province with the highest diabetes population is %s\n",
         highestPercentage);
  printf("\nThe province witht the lowest diabetes population is %s",
         lowestPercentage);

  // 3

  printf("\n\n\n-----------------------------------------------------\n");
  printf("-----------------------------------------------------\n\n\n");

  printf("The provinces above the national average are: \n");
  for (int i = 1; i < 5; i++) { // scans the different provincial averages
    if (provincialAverages[i] >
        provincialAverages[0]) { // finds minumum diabetes
      printf("%s\n", places[i]);
    }
  }

  printf("\n");

  printf("The provinces below the national average are: \n");
  for (int i = 1; i < 5; i++) { // scans the different provincial averages
    if (provincialAverages[i] <
        provincialAverages[0]) { // finds minumum diabetes
      printf("%s\n", places[i]);
    }
  }

  printf("\n\n\n-----------------------------------------------------\n");
  printf("-----------------------------------------------------\n\n\n");

  // 4

  printf("%s had the highest percentage of diabetes in %d\n\n", highestPlace,
         highestYear);
  printf("%s had the lowest percentage of diabetes in %d", lowestPlace,
         lowestYear);

  printf("\n\n\n-----------------------------------------------------\n");
  printf("End Of Calculations\n");
  printf("-----------------------------------------------------\n\n\n");

  // SECTION 3 - EXPORTING FILE TO THROW INTO GNU PLOT

  // first question which plots the average percentages based on years and
  // locations
  FILE *fpy =
      fopen("yearavg.txt", "w"); // creates a new txt file made specifically to
                                 // be then used with the gnuploteditor
  fprintf(fpy, "Year\t\tNatAvg\t\tQueAvg\t\tOntAvg\t\tAlbAvg\t\tBCAvg");
  for (int h = 0; h < 7; h++) {
    fprintf(fpy, "\n%d", years[h]);
    for (int j = 0; j < 5; j++) {
      double total = 0;
      int divider = 0;
      for (int i = 0; i < 210; i++) {
        if (location[i] == j && year[i] == h && percentage[i] != 0) {
          divider++;
          total += percentage[i];
        }
      }
      double average =
          total / divider; // finds the average percent of diabetic people for a
                           // specific location inside a loop that runs it again
                           // for every year
      fprintf(fpy, "\t\t%.3lf", average);
    }
  }
  fclose(fpy);

  // GNUplot graph script for the first graph :
  /*set terminal svg enhanced size 750, 500
set title ' Percentage of Diabetec People based on Region over the Years'
set xlabel 'Years'
set ylabel 'Average percentage of people diagnosed with Diabetes'
set xtics 1
set key top left
set style line 1 lt rgb "red" pt 6
plot 'yearavg.txt' u 1:2 t "Canada (excluding Territories)" with lp, \
                'yearavg.txt' u 1:3 t "Quebec" w lp, \
        'yearavg.txt' u 1:4 t "Ontario" w lp, \
        'yearavg.txt' u 1:5 t "Alberta" w lp , \
        'yearavg.txt' u 1:6 t "British Columbia" w lp ls 1*/

  // second question which plots the average percentages based on age range

  FILE *fpa =
      fopen("ageavg.txt", "w"); // creating a seperate file for the second plot
  fprintf(fpa, "No.\t\tAge Group\t\tNatAvg");
  for (int j = 0; j < 3; j++) {

    double total = 0;
    int divider = 0;
    for (int i = 0; i < 210; i++) {
      if (location[i] == 0 && age[i] == j && percentage[i] != 0) {
        divider++;
        total += percentage[i];
      }
    }
    double average = total / divider;
    nationalAgeAverages[j] = average;
    fprintf(fpa, "\n%d\t\t%s\t\t%.3lf", j, ageGroups[j], average);
  }
  fclose(fpa);
  // GNUplot graph script for the second graph :
  /*set terminal svg enhanced size 750, 500 background rgb 'white'
set title ' Percentage of Diabetec People based on Age Range for the Entire
Country' set xlabel 'Age Range' set ylabel 'Average percentage of people
diagnosed with Diabetes' set yrange [0:20] set xrange [-0.5:2.5] set xtics 1 set
boxwidth 0.5 set style fill solid set style line 1 lc rgb "red" set style line 2
lc rgb "blue" set style line 3 lc rgb "purple" set key left
plot "ageavg.txt" every ::1::1 using 1:3:xtic(2) title "35-49" with boxes ls 1,
\
     "ageavg.txt" every ::2::2 using 1:3:xtic(2) title "50-64" with boxes ls 2,
\ "ageavg.txt" every ::3::3 using 1:3:xtic(2) title "65+" with boxes ls 3*/

  return 0;
}
