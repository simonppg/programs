function fact_test ( )

	mex fact.cpp

	for i = 1 : 10
		j = fact ( i );
		fprintf ( 1, '  %2d  %10d\n', i, j );
	end

	return
end


