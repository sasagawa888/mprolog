
void peek(void)
{
printf("sp=%d wp=%d ac=%d bp=%d\n",sp[0],wp[0],ac[0],bp[0]);
printf("backstack\n");
printf("# sp    choice     wp     ac\n");
int i;
for(i=1;i<=bp[0];i++){
	printf("%d %d %d %d\n",backstack[i][0][0], backstack[i][0][1], backstack[i][0][2], backstack[i][0][3]);
}
printf("variant\n");
printf("#  val\n");
for(i=0;i<ac[0];i++){
    printf("%d  ",i);
	print(variant[i][0]);
}
printf("localstack\n");
for(i=0;i<sp[0];i++){
    printf("%d ",i);
	print(stack[i][0]);
}
}


void debug(void)
{
printf("sp=%d wp=%d ac=%d bp=%d\n",sp[0],wp[0],ac[0],bp[0]);
printf("backstack\n");
printf("# sp    choice     wp     ac\n");
int i;
for(i=1;i<=bp[0];i++){
	printf("%d %d %d %d\n",backstack[i][0][0], backstack[i][0][1], backstack[i][0][2], backstack[i][0][3]);
}
printf("variant\n");
printf("#  val\n");
for(i=0;i<ac[0];i++){
    printf("%d  ",i);
	print(variant[i][0]);
}
printf("localstack\n");
for(i=0;i<sp[0];i++){
    printf("%d ",i);
	print(stack[i][0]);
}
DEBUG}