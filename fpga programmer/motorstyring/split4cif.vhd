----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    17:59:16 03/10/2011 
-- Design Name: 
-- Module Name:    split4cif - Behavioral 
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

entity split4cif is
	
	port( big_number 	: in std_logic_vector (13 downto 0);
			clk			: in std_logic;
	
			number1	 	: out std_logic_vector (3 downto 0);
			number2	 	: out std_logic_vector (3 downto 0);
			number3	 	: out std_logic_vector (3 downto 0);
			number4	 	: out std_logic_vector (3 downto 0)
			);
			
end split4cif;

architecture Behavioral of split4cif is

begin

	process(clk)
	
		 variable temp_bignumber : integer range 0 to 10000 := 180;
		 variable part_number : std_logic_vector (3 downto 0) := "0000";
		 variable working : std_logic_vector (2 downto 0) := "000";
		 
	begin
		if rising_edge(clk) then 
			if working = "000" then
				temp_bignumber := conv_integer(big_number);
				working := "100";
			end if;
			if temp_bignumber > 999 then
				temp_bignumber := temp_bignumber - 1000;
				part_number := part_number + 1;
				
			elsif working = "100" then
				number4 <= part_number;
				part_number := "0000";
				working := "011";
				
			elsif temp_bignumber > 99 then
				temp_bignumber := temp_bignumber - 100;
				part_number := part_number + 1;
			
			elsif working = "011" then
				number3 <= part_number;
				part_number := "0000";
				working := "010";
				
			elsif temp_bignumber > 9 then
				temp_bignumber := temp_bignumber - 10;
				part_number := part_number + 1;
			
			elsif working = "010" then
				number2 <= part_number;
				part_number := "0000";
				working := "001";
			
			elsif working = "001" then
				number1 <= conv_std_logic_vector(temp_bignumber,4);
				part_number := "0000";
				working := "000";
			end if;
		end if;
	end process;

end Behavioral;

