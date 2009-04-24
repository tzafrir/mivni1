/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet ex 1                                          */ 
/*                                                                          */ 
/****************************************************************************/

/****************************************************************************/
/*                                                                          */ 
/* File Name : library1.h                                                   */ 
/*                                                                          */ 
/****************************************************************************/

#ifndef _234218_WET1_
#define _234218_WET1_


#ifdef __cplusplus
extern "C" {
#endif




/* Return Values
 * ----------------------------------- */
typedef enum {
	SUCCESS = 0,
	FAILURE = -1,
	INVALID_INPUT = -2,
	ALLOCATION_ERROR = -3

} StatusType;



/* Required Interface for the Data Structure
 * -----------------------------------------*/



/* Description:   Initializes a data structure with no bands in it.
 *                budget is the initial budget of ASAT.
 * Input:         DS - A pointer to the data structure.
 *                budget - ASAT's budget for the student festival.
 * Output:        None.
 * Return Values: A pointer to a new instance of the data structure - as a void* pointer.
 */
void*       Init(int budget);







/* Description:   Changes ASAT's budget for the student festival.
 * Input:         DS - A pointer to the data structure.
 *                budget - ASAT's new budget.
 * Output:        None.
 * Return Values: INVALID_INPUT - If DS==NULL or budget<0
 *                FAILURE - In case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType  ChangeBudget(void* DS, int budget);







/* Description:   Adds a new band with an ID number of bandID.
 *                price is the amount of money the band charges for a performance in the student festival.
 * Input:         DS - A pointer to the data structure.
 *                bandID - The ID of the band.
 *                price - The cost of bringing the band to the student festival.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, bandID<0 or price<0
 *                FAILURE - If bandID already exists in the database or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType  AddBand(void* DS, int bandID, int price);







/* Description:   Removes the proposal given by the band with ID bandID.
 * Input:         DS - A pointer to the data structure.
 *                bandID - The ID of the band.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or bandID<0
 *                FAILURE - If bandID doesn't exist in the database or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType  RemoveBand(void* DS, int bandID);







/* Description:   Adds votes given by students to the band with ID bandID.
 * Input:         DS - A pointer to the data structure.
 *                bandID - The ID of the band.
 *                numVotes - The number of additional votes the band got.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, bandID<0 or numVotes<=0
 *                FAILURE - If bandID doesn't exist in the database or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType  AddVotes(void* DS, int bandID, int numVotes);







/* Description:   The band with ID bandID changed their proposal.
 *                They now offer to perform in the student festival for a different amount of money, given in price.
 * Input:         DS - A pointer to the data structure.
 *                bandID - The ID of the band.
 *                price - The new price the band charges for performing in the student festival.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, bandID<0 or price<0
 *                FAILURE - If bandID doesn't exist in the database or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType  ChangePrice(void* DS, int bandID, int price);







/* Description:   All of the bands decided to give ASAT a discount, given in the parameter discount.
 *                Notice that the discount will be made only if no band's price will be negative. If so, the function does nothing.
 * Input:         DS - A pointer to the data structure.
 *                discount - The discount given by all of the bands.
 * Output:        None.
 * Return Values: INVALID_INPUT - If DS==NULL or discount<0
 *                FAILURE - If there is a band who's price after the discount is negative or in case of any other error.
 *                In that case, the function does nothing.
 *                SUCCESS - Otherwise.
 */
StatusType  ChangeAllPrices(void* DS, int discount);







/* Description:   Returns the price charged by the band with ID bandID for performing at the student festival.
 * Input:         DS - A pointer to the data structure.
 *                bandID - The ID of the band.
 * Output:        price - The address in which the price will be written.
 * Return Values: INVALID_INPUT - If DS==NULL, price==NULL or discount<0
 *                FAILURE - If the band doesn't exist or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType  GetPrice(void* DS, int bandID, int* price);







/* Description:   Returns the maximal needed budget. Meaning, the budget needed in order to bring 
 *                all of the bands to the student festival.
 * Input:         DS - A pointer to the data structure.
 * Output:        maxBudget - Maximal budget needed.
 * Return Values: INVALID_INPUT - If one of the pointers is NULL.
 *                FAILURE - In case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType  MaxNeededBudget(void* DS, int* maxBudget);







/* Description:   Returns the current list of bands which ASAT will bring to the student festival.
 *                ASAT goes over the bands by their popularity - meaning, sorted by the number of votes given to them in descending order.
 *                For each band in that order, if ASAT has enough money left to bring that band, they do.
 *                If two bands got the same number of votes, the one with the lesser price will be chosen first.
 *                If the price is identical, the one with the larger ID will be chosen first.
 *                If there are no bands, return an empty array with size=0.
 *                If there is extra money, return all of the bands.
 * Input:         DS - A pointer to the data structure.
 * Output:        bandList - An array which will be allocated by you.
 *                It will contain the IDs of the chosen bands by the order they were chosen.
 *                size - The size of the array (respectively, the number of bands chosen by ASAT).
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If one of the pointers is NULL.
 *                FAILURE - In case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType  BandList(void* DS, int** bandList, int* size);







/* Description:   Quits and deletes the database.
 *                DS should be set to NULL.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */
void        Quit(void** DS);





#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET1_ */ 

