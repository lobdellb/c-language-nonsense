/* Generates Helix DNA Structure */
/* HELIX.C */
/* 2/12/95 */
/* Bryce Lobdell */

/* Include files */
#include <stdlib.h>   
#include <stdio.h>
#include <math.h>

/* Constants */
#define PI 3.141592654

const double circle = PI*2;     /* Degrees -> Radians */
const double radtodegree =180/PI;       /* Radians -> Degrees */
const double almostzero=1;

/* Macros */
#define objects_per_twist totalobjects/twists

/* Function Prototypes */
void getargs(int numargs,char *(*args),double *totalobjects,double *twists,double *height,double *radius,double *objectradius,double *steps_object, double *rotate);
void getdata(double *totalobjects,double *twists,double *height,double *radius,double *objectradius,double *steps_object, double *rotate);
void ask(char *question,double *answer);
void limits(double totalobjects,double twists,double height,double radius,double objectradius,double steps_object);
double *calchelix(double pertwist,double twists,double height,double radius);
void povheader(FILE *dnafile,double height);
void writecone(FILE *dnafile, double numpoints, double *helix,double radius,double rotate);
void writestep(FILE *dnafile, double numpoints, double *dna,double radius,double objectstep,double wholeradius,double rotate);
void writedeoxyribose(FILE *dnafile,double numpoints, double *dna,double radius, double objectstep,double rotate);
void writephosphate(FILE *dnafile,double numpoints, double *dna,double radius, double objectstep,double rotate);
void writecolors(FILE *dnafile);
void help();

/* Main Program */
main(int numargs, char *args[])
{
/* Variable declarations, I made them all doubles for convienence. */
double rotate=0,totalobjects=20,pertwist=0,twists=1,height=50;
double radius=10,objectradius=0.5,steps_object=4,*dna_points;
FILE *dnafile;

/* If there are command line argumets process them. */
if (numargs >1)
getargs(numargs,args,&totalobjects,&twists,&height,&radius,&objectradius,&steps_object,&rotate);
/* If not get it from the keyboard. */
else
getdata(&totalobjects,&twists,&height,&radius,&objectradius,&steps_object,&rotate);

/* Set them minimum and maximum values for the variables,
if they are out of range exit with code (1) */
limits(totalobjects,twists,height,radius,objectradius,steps_object);

/* Plot the coordinates for the helix */
pertwist=objects_per_twist;
dna_points=calchelix(pertwist,twists,height,radius);

/* File Processes */
dnafile=fopen("dna.pov","w");   /* Open file */
povheader(dnafile,height);      /* Write POV 2.2 header info */
writecolors(dnafile);           /* #define's the colors */
/* Writes the cones that compose the helix structure */
writecone(dnafile,totalobjects,dna_points,objectradius,rotate);
/* Writes the cones that compose the ladder steps */
writestep(dnafile,totalobjects,dna_points,objectradius,steps_object,2*radius,rotate);
/* Writes the purple spheres that represent deoxyribose */
writedeoxyribose(dnafile,totalobjects,dna_points,objectradius,steps_object,rotate);
/* Writes the orange spheres that represent the phosphoric acid */
writephosphate(dnafile,totalobjects,dna_points,objectradius,steps_object,rotate);
fclose(dnafile);

/* All Done */
}

/* Gets data from keyboard */
void getdata(double *totalobjects,double *twists,double *height,double *radius,double *objectradius,double *steps_object, double *rotate)
{
int repeat;                                 

/* An array filled with pointers to the questions */
char *messages[7]={"How many twists?","How many objects in Helix?","How tall?","How wide?","How wide are the individual objects?","How many objects per step?","How Many degrees rotation?"};

/* An array filled with pointers to the defaults
as well as were the response will be stored */
double *variab[7];
variab[0]=twists;
variab[1]=totalobjects;
variab[2]=height;
variab[3]=radius;
variab[4]=objectradius;
variab[5]=steps_object;
variab[6]=rotate;
printf("\nEnter your value, any negative number keeps the default.");
for (repeat=0; repeat <=6; repeat++)  
{
ask(messages[repeat],variab[repeat]);
}                                                       
}

 
/*Asks the Question for getdata() */
void ask(char *question,double *answer)
{
float tmpans; 

/* Asks the question */
printf("\n%s [%.1f]:",question,*answer);

/* Takes the response */
scanf("%f",&tmpans);

/* If the answers isn't < 0 keep the answer */ 
if (!(tmpans < 0))
*answer=tmpans;
}


/* Calculates Helix */
double *calchelix(double pertwist,double twists,double height,double radius)
{
double angle,objects=twists*pertwist,current_element=0,*helix,*forward;

/* Allocate memory */
helix=calloc(objects,48);
if (helix==NULL)        /* If no memory is available exit with code (2) */
exit(2);
forward=helix;

/* Fills the memory with coords for the helix */
for (current_element=1;current_element <= objects;current_element++)                  /* Loop that will continue until */
{            

	/* a cosine is the x coord.
	a sine is the y coord, and
	the x falls a fixed amount
	with each new vector of
	coords. */

	angle=fmod(current_element,pertwist)/pertwist*circle;                   
	*(forward)=cos(angle)*radius;
	*(forward+1)=current_element/objects*height;
	*(forward+2)=sin(angle)*radius;
	*(forward+3)=-*(forward);
	*(forward+4)=*(forward+1);
	*(forward+5)=-*(forward+2);
    forward+=6;
}
/* Passes on the location of the 
array filled with the coordinates */
return helix;
}


/* Sets the values to there minimum & maximum */ 
void limits(double totalobjects,double twists,double height,double radius,double objectradius,double steps_object)
{
int terminate=0;
if ((totalobjects > 100) || (totalobjects <10))
terminate=1;
if ((twists > 15) || (twists < 0))
terminate=1;
if ((steps_object > totalobjects ) || (steps_object < 0))
terminate=1;
if (height <=0)
terminate=1;
if (radius <=0)
terminate=1;
if (objectradius <=0)
terminate=1;
if (terminate==1)
exit(1); 
}

/* Writes the POV file header */
void povheader(FILE *dnafile,double height)
{
/* Writes camera, and light_source */
fprintf(dnafile,"//DNA.POV created by HELIX.EXE\n");    
fprintf(dnafile,"//Copyright 1995, by Bryce Lobdell\n");
fprintf(dnafile,"//          FREEWARE!\n\n");
fprintf(dnafile,"camera {\n");
fprintf(dnafile,"location < 0, %.1f, -%.1f >\n",.5*height,height);
fprintf(dnafile,"up < 0, 1, 0 >\n");
fprintf(dnafile,"right < 1, 0, 0 >\n");
fprintf(dnafile,"look_at < 0, %.1f, 0 >\n",.5*height);
fprintf(dnafile,"}\n\n");
fprintf(dnafile,"object{\n");
fprintf(dnafile,"light_source{< 0, %.1f, -%.1f > color red 1 green 1 blue 1}}\n\n",.5*height,.35*height);
}

/* Writes the cones that make up the helix structure */
void writecone(FILE *dnafile, double numpoints, double *helix,double radius,double rotate)
{
double current_element;
printf("Writing Helix Structure");
fprintf(dnafile,"//makes up the helix structure\n");
fprintf(dnafile,"object {\n");
fprintf(dnafile,"union {\n");
for (current_element=1;current_element <=numpoints-1;current_element++)
{
printf(".");
fprintf(dnafile,"cone {< %.2f, %.2f, %.2f>, %.2f, < %.2f, %.2f, %.2f>, %.2f}\n",*(helix),*(helix+1),*(helix+2),radius,*(helix+6),*(helix+7),*(helix+8),radius);
fprintf(dnafile,"cone {< %.2f, %.2f, %.2f>, %.2f, < %.2f, %.2f, %.2f>, %.2f}\n",*(helix+3),*(helix+4),*(helix+5),radius,*(helix+9),*(helix+10),*(helix+11),radius);
helix=helix+6;
}
fprintf(dnafile,"rotate < 0, %.2f, 0>}\n",rotate);
fprintf(dnafile,"texture { pigment { HELIX } finish { phong 0.5 ambient 0.3 }\n");
fprintf(dnafile,"}}\n\n");
printf("Done!\n");
}

/* Writes the ladder steps */
void writestep(FILE *dnafile, double numpoints, double *dna,double radius,double objectstep,double wholeradius,double rotate)
{
double *helix;
double flag=objectstep;
double current_element;
int subscript;
int rotate2;        
int ff=6*(numpoints-1);

/* Array filled with randomw numbers,
I did this so when you do animation
the steps are the same colors from
frame to frame */
char sequence[10];
sequence[0]=1;
sequence[1]=3;
sequence[2]=0;
sequence[3]=2;
sequence[4]=2;
sequence[5]=3;
sequence[6]=0;
sequence[7]=1;
sequence[8]=1;
sequence[9]=0;

helix=dna+ff;
printf("Writing the Steps");
fprintf(dnafile,"//writes the steps\n");
for (current_element=1;current_element<=numpoints;current_element++)
{
printf(".");
if (flag==objectstep)
    {
    subscript=fmod(current_element,10);
    fprintf(dnafile,"object {\n");
	fprintf(dnafile,"cone {< %.2f, %.2f, %.2f>, %.2f,< %.2f, %.2f, %.2f>, %.2f}\n",*(helix),*(helix+1),*(helix+2),radius,*(helix+3),*(helix+4),*(helix+5),radius);
	fprintf(dnafile,"rotate <0 %.2f 0>\n",rotate);
    if (sequence[subscript]<=1)
    {
    rotate2=180*sequence[subscript];
	fprintf(dnafile,"texture { pigment { ADENTHYM } finish { phong 0.5 ambient 0.3 } scale < %.2f, 1, 1> translate < %.2f, 0, 0> rotate < 0, %.2f, 0>}}\n\n",wholeradius,0.5*wholeradius,-1*radtodegree*atan((*(helix+2)-*(helix+5)))/(*(helix)-*(helix+3)+almostzero)+rotate+rotate2);
    }
    else 
    {
    rotate2=180*(sequence[subscript]-2);
    fprintf(dnafile,"texture { pigment { GUANCYTO } finish { phong 0.5 ambient 0.3 } scale < %.2f, 1, 1> translate < %.2f, 0, 0> rotate < 0, %.2f, 0>}}\n\n",wholeradius,0.5*wholeradius,-1*radtodegree*atan((*(helix+2)-*(helix+5)))/(*(helix)-*(helix+3)+almostzero)+rotate+rotate2);
    }
    flag=0;
    }
flag++;
helix=helix-6;
}
printf("Done!\n");
}

/* Writes the purple balls */
void writedeoxyribose(FILE *dnafile,double numpoints, double *dna,double radius, double objectstep,double rotate)
{
double *helix;
double flag=objectstep;
double repeat;
int ff=6*(numpoints-1);
helix=dna+ff;
printf("Writing the Spheres");
fprintf(dnafile,"//the colored balls\n");
fprintf(dnafile,"object {\n");
fprintf(dnafile,"union {\n");
for (repeat=1;repeat<=numpoints;repeat++)
{
printf(".");
if (flag==objectstep)
{
fprintf(dnafile,"sphere {< %.2f, %.2f, %.2f> %.2f}\n",*(helix),*(helix+1),*(helix+2),3*radius);
fprintf(dnafile,"sphere {< %.2f, %.2f, %.2f> %.2f}\n",*(helix+3),*(helix+4),*(helix+5),3*radius);
flag=0;
}
flag=flag+1;
helix=helix-6;
}
fprintf(dnafile,"}\n");
fprintf(dnafile,"rotate < 0, %.2f, 0>\n",rotate); 
fprintf(dnafile,"texture { pigment { PURPLE } finish { ambient 0.3 phong 0.5 }}\n");
fprintf(dnafile,"}\n\n");
}

/* Writes the orange balls */
void writephosphate(FILE *dnafile,double numpoints, double *dna,double radius, double objectstep,double rotate)
{
double *helix;
double flag=ceil(0.5*objectstep);
double repeat;
int ff=6*(numpoints-1);
helix=dna+ff;
fprintf(dnafile,"object {\n");
fprintf(dnafile,"union {\n");
for (repeat=1;repeat<=numpoints;repeat++)
{
printf(".");
if (flag==objectstep)
{
fprintf(dnafile,"sphere {< %.2f, %.2f, %.2f> %.2f}\n",*(helix),*(helix+1),*(helix+2),3*radius);
fprintf(dnafile,"sphere {< %.2f, %.2f, %.2f> %.2f}\n",*(helix+3),*(helix+4),*(helix+5),3*radius);
flag=0;
}
flag=flag+1;
helix=helix-6;
}
fprintf(dnafile,"}\n");
fprintf(dnafile,"rotate < 0, %.2f, 0>\n",rotate);
fprintf(dnafile,"texture { pigment { ORANGE }  finish { ambient 0.3 phong 0.5}}\n");
fprintf(dnafile,"}\n\n");
printf("Done!\n");
}

/* Writes the color definitions */
void writecolors(FILE *dnafile)
{
fprintf(dnafile,"#declare ORANGE = color red 1 green 0.609375\n");
fprintf(dnafile,"#declare PURPLE = color red 0.6666 blue 0.46875\n");
fprintf(dnafile,"#declare HELIX = color red 0.5 green 0.5 blue 0.5\n");
fprintf(dnafile,"#declare ADENTHYM = pigment {\n");
fprintf(dnafile,"gradient < 1, 0, 0>\n");
fprintf(dnafile,"color_map {\n");
fprintf(dnafile,"[0 1 color red 1 color blue 1]}\n");
fprintf(dnafile,"}\n");
fprintf(dnafile,"#declare GUANCYTO = pigment {\n");
fprintf(dnafile,"gradient < 1, 0, 0>\n");
fprintf(dnafile,"color_map {\n");
fprintf(dnafile,"[0 1 color red 1 green 1 color green 0.6]}\n");
fprintf(dnafile,"}\n\n");
}

/* Processed the command line arguments, if there are any */
void getargs(int numargs,char *(*args),double *totalobjects,double *twists,double *height,double *radius,double *objectradius,double *steps_object,double *rotate)
{
char *helps[3]={"/?","-?","?"};
if ((*(*(args+1))==*helps[0])||(*(*(args+1))==*helps[1])||(*(*(args+1))==*helps[2]))
help();
if (numargs < 8)
getdata(totalobjects,twists,height,radius,objectradius,steps_object,rotate);
else
{
*totalobjects=atof((*(args+1)));
*twists=atof((*(args+2)));
*height=atof((*(args+3)));
*radius=atof((*(args+4)));
*objectradius=atof((*(args+5)));
*steps_object=atof((*(args+6)));
*rotate=atof((*(args+7)));
}
}

/* command summary, to invoke type "HELIX" and then "-?","/?", or "?" */
void help()
{
printf("HELIX.EXE\n");
printf("Written by Bryce Lobdell  1995\n\n");
printf("Command Line:\n");
printf("HELIX to tw hi rad or so ro\n\n");
printf("to:  Total number of objects\n");
printf("tw:  Twists\n");
printf("hi:  Height\n");
printf("rad:  Radius\n");
printf("or:  Individual Object Radius\n");
printf("so:  Steps per Object\n");
printf("ro:  Number of degrees rotation\n");
printf("If no command line options are provided, or\n");
printf("all 6 arguments aren't provided, it will\n");
printf("you for the values.  '/?', '-?', or '?' gives\n");
printf("this screen.\n");
exit(3);
}
