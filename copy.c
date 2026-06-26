/* reuse frame without saved arglist: jump to skip label */
int get_back_choice(int th)
{
    proof[th]++;
    if (backstack[bp[th] + 1][REUSE_BACKSTACK][th] == 1)
	return (backstack[bp[th]][CHOICE_BACKSTACK][th] + 9999);
    else if (backstack[bp[th]][REUSE_BACKSTACK][th] == 1 &&
	     backstack[bp[th]][ARGLIST_BACKSTACK][th] != UNBIND)
	return (backstack[bp[th]][CHOICE_BACKSTACK][th]);
    else if (backstack[bp[th]][REUSE_BACKSTACK][th] == 1 &&
	     backstack[bp[th]][ARGLIST_BACKSTACK][th] == UNBIND)
	return (backstack[bp[th]][CHOICE_BACKSTACK][th] + 9999);
    else
	return (backstack[bp[th]][CHOICE_BACKSTACK][th]);
    /* return choice+bias to skip */

}
