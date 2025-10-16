const tests = [
	require('./units/home-test.js')
];

async function runAllTests() {
	for (const test of tests){
		try {
			await test();
		} catch (err) {
			console.log('𐄂 Test failed', err);
		}
	}

	// let current = 0;

	// function nextTest(err) {
	// 	if (err)
	// 		console.log('𐄂 Test failed', err);
	// 	if (current < tests.length)
	// 		tests[current++](nextTest);
	// 	else
	// 		console.log('✓ All tests passed!');
	// }
	// nextTest();
}

runAllTests();