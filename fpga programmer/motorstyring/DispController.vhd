----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    15:21:10 02/24/2011 
-- Design Name: 
-- Module Name:    MuxDisp - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity DispController is
  Port ( HClk	 : in  STD_LOGIC;
			number1 : in  STD_LOGIC_vector(3 downto 0);
			number2 : in  STD_LOGIC_vector(3 downto 0);
			number3 : in  STD_LOGIC_vector(3 downto 0);
			number4 : in  STD_LOGIC_vector(3 downto 0);
			dot	 : in  STD_logic_vector(3 downto 0);
         Clk	 : out STD_LOGIC ;
			A 	 	 : out STD_LOGIC ;
			B		 : out STD_LOGIC ;
			C	 	 : out STD_LOGIC ;
			D	 	 : out STD_LOGIC ;
			E	 	 : out STD_LOGIC ;
			F	 	 : out STD_LOGIC ;
			G	 	 : out STD_LOGIC ;
			H	 	 : out STD_LOGIC ;
			chose  : out STD_LOGIC_vector(3 downto 0) := "0000"
			);
end DispController;

architecture Behavioral of DispController is

signal show : STD_LOGIC_vector(3 downto 0) := "0000";

begin

--skriver tallet number ud på det valte display
	with conv_integer(show) select	
	A <= '0' when 0|2|3|5|6|7|8|9,
		  '1' when others;
	with conv_integer(show) select	  
	B <= '0' when 0|1|2|3|4|7|8|9,
		  '1' when others;
	with conv_integer(show) select
	C <= '0' when 0|1|3|4|5|6|7|8|9,
		  '1' when others;
	with conv_integer(show) select
	D <= '0' when 0|2|3|5|6|8|9,
		  '1' when others;
	with conv_integer(show) select
	E <= '0' when 0|2|6|8,
		  '1' when others;
	with conv_integer(show) select
	F <= '0' when 0|4|5|6|8|9,
		  '1' when others;
	with conv_integer(show) select
	G <= '0' when 2|3|4|5|6|8|9,
		  '1' when others;

--Process der opretter en 1KHz clock ud fra en 50MHz clk
--Derudover vises input tallende på displayet i rigtig rækkefølge	
	process( HClk )
	
	variable scale_count : integer range 0 to 25001 := 1;
	variable Clk_state 	: std_logic := '0';
	variable display		: std_logic_vector (1 downto 0) := "00";
	
	begin
		if rising_edge(HClk) then
			scale_count := scale_count+1;
			if scale_count = 25001 then
				scale_count := 1;
				Clk_state := Clk_state XOR '1';
				Clk <= Clk_state;
				if display = "00" then
					display := "01";
					chose <= "1110";
					show <= number1;
					if dot(0) = '1' then
						H <= '0';
					else
						H <= '1';
					end if;
				elsif display = "01" then
					display := "10";
					chose <= "1101";
					show <= number2;
					if dot(1) = '1' then
						H <= '0';
					else
						H <= '1';
					end if;
				elsif display = "10" then
					display := "11";
					chose <= "1011";
					show <= number3;
					if dot(2) = '1' then
						H <= '0';
					else
						H <= '1';
					end if;
				elsif display = "11" then
					display := "00";
					chose <= "0111";
					show <= number4;
					if dot(3) = '1' then
						H <= '0';
					else
						H <= '1';
					end if;
				end if;
			end if;
		end if;
	end process;

end Behavioral;