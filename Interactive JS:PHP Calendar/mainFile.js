let currentMonth = new Month(2021,10);
currentMonth = currentMonth.nextMonth().prevMonth()
document.getElementById("month").innerHTML = stringer(currentMonth.month);
document.getElementById("year").innerHTML = currentMonth.year;
alert("Click Next Month or Prev Month to start date-displaying view")


	document.getElementById("next").addEventListener("click", function(event){
    currentMonth = currentMonth.nextMonth();
    updateCalendar();
    document.getElementById("month").innerHTML = stringer(currentMonth.month);
    document.getElementById("year").innerHTML = currentMonth.year;
    // alert("The new month is " +currentMonth.month + " " +currentMonth.year);
}, false);

document.getElementById("prev").addEventListener("click", function(event){
    currentMonth = currentMonth.prevMonth();
    updateCalendar();
    // alert("The new month is " +currentMonth.month + " " +currentMonth.year);
     document.getElementById("month").innerHTML = stringer(currentMonth.month);
     document.getElementById("year").innerHTML = currentMonth.year;
}, false);

function stringer(m){
	if(m == 10){
		return "November";
	}
	else if(m ==1){
		return "February";
	}
	else if(m == 2){
		return "March";
	}
	else if(m == 3){
		return "April";
	}
	else if(m == 4){
		return "May";
	}
	else if(m == 5){
		return "June";
	}
	else if(m == 6){
		return "July";
	}
	else if(m == 7){
		return "August";
	}
	else if(m == 8){
		return "September";
	}
	else if(m == 9){
		return "Ocotber";
	}
	else if(m == 11){
		return "December";
	}
	else{
		return "January";
		
	}
}



function updateCalendar(){
    let weeks = currentMonth.getWeeks();

    //for(let w in weeks){
        let days = weeks[0].getDates();
		document.getElementById("sunday").innerHTML = String(days[0]).substring(0,10);
		document.getElementById("monday").innerHTML = String(days[1]).substring(0,10);
		document.getElementById("tuesday").innerHTML = String(days[2]).substring(0,10);
		document.getElementById("wednesday").innerHTML = String(days[3]).substring(0,10);
		document.getElementById("thursday").innerHTML = String(days[4]).substring(0,10);
		document.getElementById("friday").innerHTML = String(days[5]).substring(0,10);
		document.getElementById("saturday").innerHTML = String(days[6]).substring(0,10);
		days = weeks[1].getDates();
		document.getElementById("sunday2").innerHTML = String(days[0]).substring(0,10);
		document.getElementById("monday2").innerHTML = String(days[1]).substring(0,10);
		document.getElementById("tuesday2").innerHTML = String(days[2]).substring(0,10);
		document.getElementById("wednesday2").innerHTML = String(days[3]).substring(0,10);
		document.getElementById("thursday2").innerHTML = String(days[4]).substring(0,10);
		document.getElementById("friday2").innerHTML = String(days[5]).substring(0,10);
		document.getElementById("saturday2").innerHTML = String(days[6]).substring(0,10);
		days = weeks[2].getDates();
		document.getElementById("sunday3").innerHTML = String(days[0]).substring(0,10);
		document.getElementById("monday3").innerHTML = String(days[1]).substring(0,10);
		document.getElementById("tuesday3").innerHTML = String(days[2]).substring(0,10);
		document.getElementById("wednesday3").innerHTML = String(days[3]).substring(0,10);
		document.getElementById("thursday3").innerHTML = String(days[4]).substring(0,10);
		document.getElementById("friday3").innerHTML = String(days[5]).substring(0,10);
		document.getElementById("saturday3").innerHTML = String(days[6]).substring(0,10);
		days = weeks[3].getDates();
		document.getElementById("sunday4").innerHTML = String(days[0]).substring(0,10);
		document.getElementById("monday4").innerHTML = String(days[1]).substring(0,10);
		document.getElementById("tuesday4").innerHTML = String(days[2]).substring(0,10);
		document.getElementById("wednesday4").innerHTML = String(days[3]).substring(0,10);
		document.getElementById("thursday4").innerHTML = String(days[4]).substring(0,10);
		document.getElementById("friday4").innerHTML = String(days[5]).substring(0,10);
		document.getElementById("saturday4").innerHTML = String(days[6]).substring(0,10);
		days = weeks[4].getDates();
		document.getElementById("sunday5").innerHTML = String(days[0]).substring(0,10);
		document.getElementById("monday5").innerHTML = String(days[1]).substring(0,10);
		document.getElementById("tuesday5").innerHTML = String(days[2]).substring(0,10);
		document.getElementById("wednesday5").innerHTML = String(days[3]).substring(0,10);
		document.getElementById("thursday5").innerHTML = String(days[4]).substring(0,10);
		document.getElementById("friday5").innerHTML = String(days[5]).substring(0,10);
		document.getElementById("saturday5").innerHTML =String(days[6]).substring(0,10);
        //alert(Dates = days.toString());
        // for(let d in days){

        //     console.log(days[d].toISOString());
        //}
    //}

}



(function () {
	"use strict";

	/* Date.prototype.deltaDays(n)
	 * 
	 * Returns a Date object n days in the future.
	 */
	Date.prototype.deltaDays = function (n) {
		// relies on the Date object to automatically wrap between months for us
		return new Date(this.getFullYear(), this.getMonth(), this.getDate() + n);
	};

	/* Date.prototype.getSunday()
	 * 
	 * Returns the Sunday nearest in the past to this date (inclusive)
	 */
	Date.prototype.getSunday = function () {
		return this.deltaDays(-1 * this.getDay());
	};
}());

/** Week
 * 
 * Represents a week.
 * 
 * Functions (Methods):
 *	.nextWeek() returns a Week object sequentially in the future
 *	.prevWeek() returns a Week object sequentially in the past
 *	.contains(date) returns true if this week's sunday is the same
 *		as date's sunday; false otherwise
 *	.getDates() returns an Array containing 7 Date objects, each representing
 *		one of the seven days in this month
 */
function Week(initial_d) {
	"use strict";

	this.sunday = initial_d.getSunday();
		
	
	this.nextWeek = function () {
		return new Week(this.sunday.deltaDays(7));
	};
	
	this.prevWeek = function () {
		return new Week(this.sunday.deltaDays(-7));
	};
	
	this.contains = function (d) {
		return (this.sunday.valueOf() === d.getSunday().valueOf());
	};
	
	this.getDates = function () {
		var dates = [];
		for(var i=0; i<7; i++){
			dates.push(this.sunday.deltaDays(i));
		}
		return dates;
	};
}

/** Month
 * 
 * Represents a month.
 * 
 * Properties:
 *	.year == the year associated with the month
 *	.month == the month number (January = 0)
 * 
 * Functions (Methods):
 *	.nextMonth() returns a Month object sequentially in the future
 *	.prevMonth() returns a Month object sequentially in the past
 *	.getDateObject(d) returns a Date object representing the date
 *		d in the month
 *	.getWeeks() returns an Array containing all weeks spanned by the
 *		month; the weeks are represented as Week objects
 */


function Month(year, month) {
	"use strict";
	
	this.year = year;
	this.month = month;

	this.nextMonth = function () {
		return new Month( year + Math.floor((month+1)/12), (month+1) % 12);
	};
	
	this.prevMonth = function () {
		return new Month( year + Math.floor((month-1)/12), (month+11) % 12);
	};
	
	this.getDateObject = function(d) {
		return new Date(this.year, this.month, d);
	};
	
	this.getWeeks = function () {
		var firstDay = this.getDateObject(1);
		var lastDay = this.nextMonth().getDateObject(0);
		
		var weeks = [];
		var currweek = new Week(firstDay);
		weeks.push(currweek);
		while(!currweek.contains(lastDay)){
			currweek = currweek.nextWeek();
			weeks.push(currweek);
		}
		
		return weeks;
	};
}






